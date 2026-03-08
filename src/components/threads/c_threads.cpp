// FIXME: Crash after/before (?) reload all modules (i dont know how fix this at the current time)
// NOTE: I think error in separate thread. Error: 
#include "components/threads/c_threads.hpp"
#include "components/net/c_net.hpp"
#include <mutex>
#include <thread>
#include "SDL3/SDL_timer.h"
#include "ulog.h"
#include "components/properties/c_properties.hpp"
#include "tracy/Tracy.hpp"

namespace Jila {

#define S(T) std::shared_ptr<T>

typedef std::variant<
    S(IntProperty), S(FloatProperty), 
    S(BoolProperty), S(CharProperty)
> THSupportTypes;
static std::mutex global_mutex;
static std::map<std::string, THSupportTypes> shared_scope = {};

// for tracy
// NOTE: move to separate file? Maybe.
template <typename T> constexpr const char* type_name();

template <>
constexpr const char* type_name<FloatProperty>()
{ return "FloatProperty"; }

template <>
constexpr const char* type_name<IntProperty>()
{ return "IntProperty"; }

template <>
constexpr const char* type_name<CharProperty>()
{ return "CharProperty"; }

template <>
constexpr const char* type_name<BoolProperty>()
{ return "BoolProperty"; }
//

template<typename T>
std::shared_ptr<T> SharedScope_Get(const std::string_view key) {
    ZoneScoped;
    ZoneTextF("Variable: %s - Type: %s", key.data(), type_name<T>());
    std::lock_guard<std::mutex> lock(global_mutex);

    auto it = shared_scope.find(key.data());

    if (it != shared_scope.end()) {
        return std::get<std::shared_ptr<T>>(it->second);
    }

    return NULL;
}

template<typename PropT, typename ArgT>
std::shared_ptr<PropT> SharedCreate(const std::string_view key, ArgT value) {
    ZoneScoped;
    ZoneTextF("Variable: %s - Type: %s", key.data(), type_name<PropT>());
    std::lock_guard<std::mutex> lock(global_mutex);
    auto prop = std::make_shared<PropT>(value);
    shared_scope[key.data()] = prop;
    return prop;
}

void shared_functions(sol::state& state) {
    state.set_function(
        "Jila_Sleep", [](int ms) {
        SDL_Delay(ms);
    });

    // SharedStorage: Create functions
    state.set_function("SharedScope_CreateF", &SharedCreate<FloatProperty, float>);
    state.set_function("SharedScope_CreateI", &SharedCreate<IntProperty, int>);
    state.set_function("SharedScope_CreateC", &SharedCreate<CharProperty, std::string_view>);
    state.set_function("SharedScope_CreateB", &SharedCreate<BoolProperty, bool>);

    // SharedStorage: Get functions
    state.set_function("SharedScope_GetF", &SharedScope_Get<FloatProperty>);
    state.set_function("SharedScope_GetI", &SharedScope_Get<IntProperty>);
    state.set_function("SharedScope_GetC", &SharedScope_Get<CharProperty>);
    state.set_function("SharedScope_GetB", &SharedScope_Get<BoolProperty>);

    // SharedStorage: Delete function
    state.set_function(
        "SharedScope_Delete", [](const std::string_view key) {
        std::lock_guard<std::mutex> lock(global_mutex);
        return shared_scope.erase(key.data()) > 0;
    });
}

inline void ThreadError(std::string_view threadName, std::string_view error) {
    ulog_error((std::string("In thread ") + std::string(threadName)).data());
    ulog_error(error.data());
}

void _RunSeparated(
    sol::basic_bytecode<> byteCode, 
    std::string moduleName
) {
    ZoneScoped;
    ZoneTextF("Thread name: %s", moduleName.c_str());

    sol::state threaded_state;

    shared_functions(threaded_state);
    
    threaded_state.open_libraries(
        sol::lib::base, sol::lib::table, 
        sol::lib::math, sol::lib::string
    );
    PropertiesComponent::Init(&threaded_state);

    #ifdef JILA_NET
    NetComponent::Init(&threaded_state);
    #endif
    
    auto m = threaded_state.do_string(
        byteCode.as_string_view(),
        sol::detail::default_chunk_name(),
        sol::load_mode::binary
    );
    #ifndef JILA_RELEASE
    if (!m.valid()) {
        sol::error err = m;
        ThreadError(moduleName, err.what());
    }
    #endif
}
    
void _Go(sol::function func, std::string threadName) {
    ZoneScoped;
    ZoneTextF("Thread name: %s", threadName.c_str());

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
