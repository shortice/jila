#ifdef JILA_DATABASE
#include "components/database/c_database.hpp"
#include "misc.hpp"
#include "leveldb/db.h"

namespace Jila {

namespace DataBase_Component {

typedef std::shared_ptr<leveldb::DB> DataBase;

DataBase Data_Create(
    std::string name
) {
    leveldb::DB* data;
    leveldb::Options opts{};

    opts.create_if_missing = true;

    leveldb::DB::Open(
        opts,
        name,
        &data
    );

    return MakeSafeMemory<leveldb::DB>(
        data,
        [](leveldb::DB* data) {
            delete data;
        }
    );
}

std::string Data_Get(DataBase data, std::string key) {
    std::string value;
    
    data->Get(
        leveldb::ReadOptions(),
        key,
        &value
    );

    return value;
}

bool Data_Set(DataBase data, std::string key, std::string value) {
    return data->Put(
        leveldb::WriteOptions(),
        key,
        value
    ).ok();
}

bool Data_Delete(DataBase data, std::string key) {
    return data->Delete(
        leveldb::WriteOptions(),
        key
    ).ok();
}

bool Data_IsExists(DataBase data, std::string key) {
    std::string value;
    
    return data->Get(
        leveldb::ReadOptions(),
        key,
        &value
    ).IsNotFound();
}

bool Init(sol::state* state) {
    state->set_function(
        "Data_Create",
        &Data_Create
    );

    state->set_function(
        "Data_Get",
        &Data_Get
    );

    state->set_function(
        "Data_Set",
        &Data_Set
    );

    state->set_function(
        "Data_Delete",
        &Data_Delete
    );

    state->set_function(
        "Data_IsExists",
        &Data_IsExists
    );

    return true;
}


void Quit(sol::state* state) {

}

}

}
#endif