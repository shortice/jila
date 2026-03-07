#ifdef JILA_DATABASE
#include "components/database/c_kv.hpp"
#include "misc.hpp"
#include "sqlite3/sqlite3.h"
#include "SDL3/SDL_error.h"
#include "proxy.hpp"

namespace Jila {
namespace DataBase_Component {

typedef std::shared_ptr<Proxy<sqlite3>> KvDataBase;

KvDataBase Kv_Connect(std::string_view path) {
    sqlite3* db = nullptr;
    int rc = sqlite3_open(path.data(), &db);
    
    if (rc != SQLITE_OK) {
        SDL_SetError("SQLite Error: %s", sqlite3_errmsg(db));
        sqlite3_close(db);
        return NULL;
    }

    const char* create_sql = "CREATE TABLE IF NOT EXISTS kv_store (key TEXT PRIMARY KEY, value TEXT);";
    char* err_msg = nullptr;

    if (sqlite3_exec(
        db,
        create_sql,
        nullptr,
        nullptr, 
        &err_msg
    ) != SQLITE_OK) {
        SDL_SetError("SQLite Init Error: %s", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return NULL;
    }

    return MakeSafeMemory<Proxy<sqlite3>>(
        new Proxy(db),
        [](Proxy<sqlite3>* db) {
            sqlite3_close(db->proxy);
        }
    );
}

bool Kv_Set(KvDataBase db, std::string key, std::string value) {
    if (!db) return false;

    const char* sql = "INSERT OR REPLACE INTO kv_store (key, value) VALUES (?, ?);";
    sqlite3_stmt* stmt;
    
    if (sqlite3_prepare_v2(
        db.get()->proxy, 
        sql, 
        -1, 
        &stmt, 
        nullptr
    ) != SQLITE_OK) {
        SDL_SetError("SQLite Prepare Error: %s", sqlite3_errmsg(db.get()->proxy));
        return false;
    }

    sqlite3_bind_text(stmt, 1, key.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, value.c_str(), -1, SQLITE_TRANSIENT);

    int rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    if (rc != SQLITE_DONE) {
        SDL_SetError("SQLite Step Error: %s", sqlite3_errmsg(db.get()->proxy));
        return false;
    }

    return true;
}

std::string Kv_Get(KvDataBase db, std::string key) {
    if (!db) return "";

    const char* sql = "SELECT value FROM kv_store WHERE key = ?;";
    sqlite3_stmt* stmt;
    std::string result = "";

    if (sqlite3_prepare_v2(
        db.get()->proxy, 
        sql, 
        -1, 
        &stmt, 
        nullptr
    ) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, key.c_str(), -1, SQLITE_TRANSIENT);

        if (sqlite3_step(stmt) == SQLITE_ROW) {
            const unsigned char* text = sqlite3_column_text(stmt, 0);
            if (text) {
                result = reinterpret_cast<const char*>(text);
            }
        }

        sqlite3_finalize(stmt);
    }

    return result;
}

void Kv_Delete(KvDataBase db, std::string key) {
    if (!db) return;

    const char* sql = "DELETE FROM kv_store WHERE key = ?;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(
        db.get()->proxy, 
        sql, 
        -1, 
        &stmt, 
        nullptr
    ) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, key.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
    }
}

bool Kv_IsExist(KvDataBase db, std::string key) {
    if (!db) return false;

    const char* sql = "SELECT 1 FROM kv_store WHERE key = ? LIMIT 1;";
    sqlite3_stmt* stmt;
    bool exists = false;

    if (sqlite3_prepare_v2(
        db.get()->proxy, 
        sql, 
        -1, 
        &stmt, 
        nullptr
    ) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, key.c_str(), -1, SQLITE_TRANSIENT);
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            exists = true;
        }
        sqlite3_finalize(stmt);
    }
    return exists;
}

void bindKv(sol::state* state) {
    state->new_usertype<Proxy<sqlite3>>("Jila_KvDB");

    state->set_function("Jila_Kv_Connect", &Kv_Connect);
    state->set_function("Jila_Kv_Set", &Kv_Set);
    state->set_function("Jila_Kv_Get", &Kv_Get);
    state->set_function("Jila_Kv_Delete", &Kv_Delete);
    state->set_function("Jila_Kv_IsExist", &Kv_IsExist);
}

}
}
#endif