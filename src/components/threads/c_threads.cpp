#include "components/threads/c_threads.hpp"
#include <thread>
#include "SDL3/SDL_stdinc.h"
#include "SDL3/SDL_events.h"
#include "SDL3/SDL_timer.h"

namespace Jila {

enum _StatusCode : Uint8 { 
    STARTING, 
    RUNNING, 
    COMPLETED, 
    ERROR 
};

template <typename T> T _get(void *var) {
    T _ = *(T *)var;
    delete (T *)var;
    return _;
}
    
struct ThreadMessage {
    std::string threadName;
    std::variant<double, std::string, sol::lua_nil_t> var;
    _StatusCode statusCode;
};
    
void _PushThreadMessage(ThreadMessage *message) {
    SDL_Event event;
    SDL_zero(event);
    event.type = SDL_EVENT_USER;
    event.user.code = 1002;
    event.user.data1 = message;
    
    SDL_PushEvent(&event);
}
    
void _PushThreadMessageLua(
    std::string threadName,
    sol::object m) {
    ThreadMessage *msg = new ThreadMessage{};
    msg->threadName = threadName;
    msg->statusCode = RUNNING;
    
    if (m.get_type() == sol::type::number) {
        msg->var = m.as<double>();
    }
    
    if (m.get_type() == sol::type::string) {
        msg->var = m.as<std::string>();
    }
    
    if (m.get_type() == sol::type::nil) {
        msg->var = sol::nil;
    }
    
    _PushThreadMessage(msg);
}
    
void _RunSeparated(
    sol::basic_bytecode<> byteCode, 
    std::string moduleName
) {
    ThreadMessage *start_msg = new ThreadMessage{};
    start_msg->threadName = moduleName;
    start_msg->statusCode = STARTING;
    _PushThreadMessage(start_msg);
    
    sol::state threaded_state;
    
    threaded_state.set_function("SDL_Delay", [](int seconds) {
        SDL_Delay(seconds * 1000);
    });
    
    threaded_state.set_function(
        "PushThreadMessage", 
        &_PushThreadMessageLua
    );
    
    threaded_state.open_libraries(
        sol::lib::base, sol::lib::table, 
        sol::lib::math, sol::lib::string
    );
    
    auto m = threaded_state.do_string(
        byteCode.as_string_view(),
        sol::detail::default_chunk_name(),
        sol::load_mode::binary
    );
    
    ThreadMessage *msg = new ThreadMessage{};
    msg->threadName = moduleName;
    
    if (m.valid()) {
        msg->statusCode = COMPLETED;
    
        if (m.get_type() == sol::type::number) {
            msg->var = m.get<double>();
        }
    
        if (m.get_type() == sol::type::string) {
            msg->var = m.get<std::string>();
        }
    
        if (m.get_type() == sol::type::nil) {
            msg->var = sol::nil;
        }
    } else {
        msg->statusCode = ERROR;
        sol::error err = m;
        msg->var = err.what();
    }
    
    _PushThreadMessage(msg);
}
    
ThreadMessage _GetThreadMessage(SDL_UserEvent &event) {
    ThreadMessage msg = *(ThreadMessage *)event.data1;
    delete (ThreadMessage *)event.data1;
    return msg;
}
    
void _Go(sol::function func, std::string threadName) {
    sol::basic_bytecode byteCode = (func.dump());
    
    std::thread d(_RunSeparated, byteCode, threadName);
    d.detach();
}

namespace ThreadsComponent {

bool Init(sol::state *state) {
    state -> new_enum(
        "ThreadStatusCode",
        "STARTING", _StatusCode::STARTING,
        "COMPLETED", _StatusCode::COMPLETED,
        "ERROR", _StatusCode::ERROR,
        "RUNNING", _StatusCode::RUNNING
    );

    state -> new_usertype<ThreadMessage>(
        "ThreadMessage",
        "threadName", sol::readonly(&ThreadMessage::threadName),
        "statusCode", sol::readonly(&ThreadMessage::statusCode),
        "var", sol::readonly(&ThreadMessage::var)
    );

    state -> set_function(
        "Go",
        &_Go
    );

    state -> set_function(
        "GetThreadMessage",
        &_GetThreadMessage
    );

    return true;
}

void Quit(sol::state *state) {}

}

}
