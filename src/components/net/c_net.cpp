#ifdef JILA_NET
#include "components/net/c_net.hpp"
#include "cpr/cpr.h"
#include "cpr/response.h"
#include "sol/sol.hpp"
#include "lua_modules/_json.h"

namespace Jila {

namespace NetComponent {

cpr::Response Get(std::string url) {
    return cpr::Get(
        cpr::Url{url}
    );
}

cpr::Response Post_V1(std::string_view url) {
    return cpr::Post(
        cpr::Url{url}
    );
}

cpr::Response Post_V2(std::string_view url, std::string_view json) {
    return cpr::Post(
        cpr::Url{url},
        cpr::Body{json},
        cpr::Header{{"Content-Type", "application/json"}}
    );
}

std::optional<std::string> Response_GetHeaderValue(
    cpr::Response& response, std::string key
) {
    auto value = response.header.find(key);

    if (value == response.header.end()) {
        return std::nullopt;
    }

    return value->second;
}

bool Init(sol::state* state) {
    (*state)["json"] = state->script(
        std::string(
            __json_lua, 
            __json_lua + __json_lua_len
        )
    ); // json module
    
    state->new_usertype<cpr::Response>(
        "Response",
        "status_code", sol::readonly(&cpr::Response::status_code),
        "text", sol::readonly(&cpr::Response::text),
        "raw_header", sol::readonly(&cpr::Response::raw_header)
    );

    state->set_function(
        "Response_GetHeaderValue",
        &Response_GetHeaderValue
    );

    state->set_function(
        "Get",
        &Get
    );

    state->set_function(
        "Post",
        sol::overload(
            &Post_V1,
            &Post_V2
        )
    );

    return true;
}

void Quit(sol::state* state) {

}

}

}
#endif