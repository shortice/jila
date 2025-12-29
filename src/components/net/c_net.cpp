#ifdef JILA_NET
#include "components/net/c_net.hpp"
#include "cpr/cpr.h"
#include "cpr/response.h"
#include "sol/sol.hpp"

namespace Jila {

namespace NetComponent {

cpr::Response Get(std::string url) {
    return cpr::Get(
        cpr::Url{url}
    );
}

cpr::Response Post(std::string url, std::map<std::string, std::string> params) {
    cpr::Parameters _params;

    for (auto _ : params) {
        _params.Add({_.first, _.second});
    }

    return cpr::Post(
        cpr::Url{url},
        _params
    );
}

// TODO: make download function

std::string Response_GetHeaderValue(cpr::Response& response, std::string key) {
    auto value = response.header.find(key);

    if (value == response.header.end()) {
        return "";
    }

    return value->second;
}

bool Init(sol::state* state) {
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
        &Post
    );

    return true;
}

void Quit(sol::state* state) {

}

}

}
#endif