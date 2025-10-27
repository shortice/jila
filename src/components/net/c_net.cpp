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

std::string GetHeaderValue(cpr::Response& response, std::string key) {
    auto value = response.header.find(key);

    if (value == response.header.end()) {
        return "";
    }

    return value->second;
}

bool Init(sol::state* state) {
    state->new_usertype<cpr::Response>(
        "Response",
        "status_code", &cpr::Response::status_code,
        "text", &cpr::Response::text,
        "getHeaderValue", &GetHeaderValue,
        "raw_header", &cpr::Response::raw_header
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
