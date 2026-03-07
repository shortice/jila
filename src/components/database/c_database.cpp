#ifdef JILA_DATABASE
#include "components/database/c_database.hpp"
#include "components/database/c_kv.hpp"
#include "misc.hpp"
#include "SDL3/SDL_error.h"
#include "sqlite3/sqlite3.h"

namespace Jila {

namespace DataBase_Component {

struct DB {
    sqlite3* conn;
    std::vector<std::array<std::string, 2>> objects;
};

typedef std::shared_ptr<DB> DataBase;

DataBase Data_Connect(
    std::string_view path
) {
    sqlite3* db;

    int rc = sqlite3_open(path.data(), &db);

    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        SDL_SetError("%s", sqlite3_errmsg(db));
        return nullptr;
    }

    return MakeSafeMemory<DB>(
        new DB {db, {}},
        [](DB* db) {
            sqlite3_close(db -> conn);
        }
    );
}

int callback(
    void *db,
    int argc,
    char **argv,
    char **azColName
) {
    int i;

    DataBase* _db = (DataBase*)db;

    for (i = 0; i < argc; i++) {
        (*_db)->objects.push_back({
            azColName[i],
            argv[i] ? argv[i] : "NULL"
        });
    }

    return nullptr;
}

bool Data_Exec(DataBase db, std::string_view sql) {
    char* err = 0;

    if (db->objects.size() > 0) {
        db->objects.clear();
    }

    int rc = sqlite3_exec(
        db->conn, sql.data(), &callback, &db, &err
    );

    if (rc != SQLITE_OK) {
        SDL_SetError("%s", err);
        sqlite3_free(err);
        return false;
    }

    return true;
}

bool Init(sol::state* state) {
    state->new_usertype<DB>(
        "Jila_DB",
        "objects", sol::readonly(&DB::objects)
    );

    state->set_function(
        "Jila_Data_Connect",
        &Data_Connect
    );

    state->set_function(
        "Jila_Data_Exec",
        &Data_Exec
    );

    bindKv(state);

    return true;
}


void Quit(sol::state* state) {

}

}

}
#endif