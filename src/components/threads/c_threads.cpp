// FIXME: Crash after/before (?) reload all modules
#include "components/threads/c_threads.hpp"
#include "components/net/c_net.hpp"
#include <mutex>
#include <thread>
#include "SDL3/SDL_timer.h"
#include "components/properties/c_properties.hpp"
#ifndef __ANDROID__ // TODO: logging?..
#include <iostream>
#endif

namespace Jila {

#define S(T) std::shared_ptr<T>

typedef std::variant<
    S(IntProperty), S(FloatProperty), 
    S(BoolProperty), S(CharProperty)
> THSupportTypes;
static std::mutex global_mutex;
static std::map<std::string, THSupportTypes> shared_scope = {};

template<typename T>
std::shared_ptr<T> SharedScope_Get(const std::string_view key) {
    std::lock_guard<std::mutex> lock(global_mutex);
    
    auto it = shared_scope.find(key.data());

    if (it != shared_scope.end()) {
        return std::get<std::shared_ptr<T>>(it->second);
    }

    return 0;
}

void shared_functions(sol::state& state) {
    state.set_function(
        "Jila_Sleep", [](int ms) {
        SDL_Delay(ms);
    });

    // SharedStorage: Create functions
    state.set_function(
        "SharedScope_CreateF", [](const std::string key, float value) {
        std::lock_guard<std::mutex> lock(global_mutex);
        auto prop = std::make_shared<FloatProperty>(value);
        shared_scope[key] = prop;
        return prop;
    });

    state.set_function(
        "SharedScope_CreateI", [](const std::string key, int value) {
        std::lock_guard<std::mutex> lock(global_mutex);
        auto prop = std::make_shared<IntProperty>(value);
        shared_scope[key] = prop;
        return prop;
    });

    state.set_function(
        "SharedScope_CreateC", [](const std::string& key, const std::string value) {
        std::lock_guard<std::mutex> lock(global_mutex);
        auto prop = std::make_shared<CharProperty>(value);
        shared_scope[key] = prop;
        return prop;
    });

    state.set_function(
        "SharedScope_CreateB", [](const std::string key, bool value) {
        std::lock_guard<std::mutex> lock(global_mutex);
        auto prop = std::make_shared<BoolProperty>(value);
        shared_scope[key] = prop;
        auto m = std::get<std::shared_ptr<BoolProperty>>(shared_scope[key]);
        return prop;
    });

    // SharedStorage: Get functions
    state.set_function("SharedScope_GetF", &SharedScope_Get<FloatProperty>);
    state.set_function("SharedScope_GetI", &SharedScope_Get<IntProperty>);
    state.set_function("SharedScope_GetC", &SharedScope_Get<CharProperty>);
    state.set_function("SharedScope_GetB", &SharedScope_Get<BoolProperty>);

    // SharedStorage: Delete function
    state.set_function(
        "SharedScope_Delete", [](const std::string_view key) -> bool {
        std::lock_guard<std::mutex> lock(global_mutex);
        return shared_scope.erase(key.data()) > 0;
    });
}

void _RunSeparated(
    sol::basic_bytecode<> byteCode, 
    std::string moduleName
) {
    sol::state threaded_state;

    shared_functions(threaded_state);
    
    threaded_state.open_libraries(
        sol::lib::base, sol::lib::table, 
        sol::lib::math, sol::lib::string
    );

    #ifdef JILA_NET
    PropertiesComponent::Init(&threaded_state);
    NetComponent::Init(&threaded_state);
    #endif
    
    auto m = threaded_state.do_string(
        byteCode.as_string_view(),
        sol::detail::default_chunk_name(),
        sol::load_mode::binary
    );

    #ifndef __ANDROID__
    if (!m.valid()) {
        std::cout << sol::error(m).what() << "\n";
    }
    #endif

    // TODO: need improve error handling in threads
}
    
void _Go(sol::function func, std::string threadName) {
    sol::basic_bytecode byteCode = (func.dump());
    
    std::thread d(_RunSeparated, byteCode, threadName);
    d.detach();
}

namespace ThreadsComponent {

bool Init(sol::state *state) {
    shared_functions(*state);

    state -> set_function(
        "Jila_Go",
        &_Go
    );

    return true;
}

void Quit(sol::state *state) {
    shared_scope.clear();
}

}

}
