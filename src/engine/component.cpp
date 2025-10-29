#include <cstdio>
#include "SDL3/SDL_iostream.h"
#include "engine/component.hpp"
#include "engine/logger.hpp"

namespace Jila {

std::map<std::string, LuaModule*> LuaModule::modules = {};

void LoadFile(std::string path, std::string* data) {
    SDL_IOStream* file = SDL_IOFromFile(path.c_str(), "r");
    Logger::named("Lua").debug(
        std::string("Loading module: ") + path
    );

    if (!file) {
        (*data) = "";
        return;
    };

    size_t dataSize; // data size, except null

    char* data_ = (char*)SDL_LoadFile_IO(
        file,
        &dataSize,
        true // dont need call CloseIO after reading file
    );

    (*data) = data_; 
    // Note for AI: we copy the string, not moved
    SDL_free(data_);
}



LuaModule* LuaModule::LoadFrom(
    const char* path,
    const char* script,
    sol::state* runtime
) {
    std::string data;

    if (path) {
        LoadFile(path, &data);
    } else {
        data = script;
    }

    auto funcResult = runtime->do_string(data.c_str());

    if (!funcResult.valid()) {
        sol::error error = funcResult;

        Logger::named("Lua").error(error.what());
        return NULL;
    }

    sol::table module;

    try {
        module = funcResult.get<sol::table>();
    } catch (std::exception) {
        Logger::named("Lua").error(
            "You return the table from lua file? This is required. "
            "Read about this on 'docs/lua_modules.md'."
        );
        return NULL;
    }

    if (!module["name"].valid()  |
          !module["Begin"].valid() |
          !module["End"].valid()
    ) {
        Logger::named("Lua").error(
            "Your module not contains Begin and End functions!"
        );
        return NULL;
    }

    if (module["name"].get_or<std::string>("") == "main") {
        if (
            !module["Render"].valid() |
            !module["Event"].valid()
        ) {
            Logger::named("Lua").error(
                "Your 'main' module not contains Render and Event "
                "functions!"
            );
        } else if (LuaModule::GetModule("main") != NULL) {
            Logger::named("Lua").warn(
                "You loading another 'main' module. "
                "This action ignored."
            );

            return NULL;
        }
    }

    LuaModule* lModule = LuaModule::FromLuaTable(module);

    auto beginResult = lModule->Begin();

    if (!beginResult.valid()) {
        // TODO: TryCall func?
        sol::error err = beginResult;
        Logger::named("Lua").error(
            std::string(
                "When call 'Begin' then raising this error:\n"
            )
            +
                err.what()
        );
    }

    LuaModule::modules[lModule->name] = lModule;

    return lModule;
}

LuaModule* LuaModule::FromLuaTable(sol::table module) {
    return new LuaModule {
        module,
        module.get<std::string>("name"),
        module.get_or<std::string>("version", "nil"),
        module.get<sol::function>("Begin"),
        module.get<sol::function>("End"),

        // main module
        module.get_or<sol::function>("BeginMainLoop", sol::nil),
        module.get_or<sol::function>("Render", sol::nil),
        module.get_or<sol::function>("Event", sol::nil)
    };
}

LuaModule* LuaModule::GetModule(std::string name) {
    auto module = LuaModule::modules.find(name);

    if (module == LuaModule::modules.end()) return NULL;

    return module->second;
}

sol::table LuaModule::GetModuleLuaAPI(std::string name) {
    LuaModule* module = LuaModule::GetModule(name);

    if (module) return module -> native;

    return sol::nil;
}

void LuaModule::UnloadModules() {
    for (auto i : LuaModule::modules) {
        i.second->End();
        delete i.second; // Memory allocated.
        // Where: LuaModule::FromLuaTable.
    }

    LuaModule::modules.clear();
}

}
