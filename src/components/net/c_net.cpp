#ifdef JILA_NET
#include "components/net/c_net.hpp"
#include <curl/curl.h>
#include "sol/sol.hpp"
#include "lua_modules/_json.h"
#include <string>
#include <vector>
#include <map>
#include <optional>

namespace Jila {

namespace NetComponent {

struct Response {
    long status_code = 0;
    std::string text;
    std::string raw_header;
    std::map<std::string, std::string> header;
};

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    size_t totalSize = size * nmemb;
    auto* responseText = (std::string*)(userp);
    responseText->append((char*)(contents), totalSize);
    return totalSize;
}

static size_t HeaderCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    size_t totalSize = size * nmemb;
    auto* response = (Response*)(userp);
    std::string headerLine((char*)(contents), totalSize);
    response->raw_header += headerLine;

    size_t colonPos = headerLine.find(':');
    if (colonPos != std::string::npos) {
        std::string key = headerLine.substr(0, colonPos);
        std::string value = headerLine.substr(colonPos + 1);

        auto trim = [](std::string& s) {
            s.erase(0, s.find_first_not_of(" \t\r\n"));
            size_t last = s.find_last_not_of(" \t\r\n");
            if (last != std::string::npos) {
                s.erase(last + 1);
            }
        };
        trim(key);
        trim(value);
        
        if (!key.empty()) {
            response->header[key] = value;
        }
    }

    return totalSize;
}

static Response PerformRequest(
    std::string_view url, 
    bool isPost = false, 
    std::string_view postData = "", 
    const std::vector<std::string>& extraHeaders = {}
) {
    Response response;
    CURL* curl = curl_easy_init();
    if (!curl) return response;

    curl_easy_setopt(curl, CURLOPT_URL, url.data());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response.text);
    curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, HeaderCallback);
    curl_easy_setopt(curl, CURLOPT_HEADERDATA, &response);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "jila/1.0");

    struct curl_slist* headers = nullptr;
    for (const auto& h : extraHeaders) {
        headers = curl_slist_append(headers, h.c_str());
    }

    if (isPost) {
        curl_easy_setopt(curl, CURLOPT_POST, CURLOPT_WRITEDATA);
        if (!postData.empty()) {
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postData.data());
            curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)postData.size());
        }
    }

    if (headers) {
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    }

    CURLcode res = curl_easy_perform(curl);
    if (res == CURLE_OK) {
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response.status_code);
    }

    if (headers) {
        curl_slist_free_all(headers);
    }
    curl_easy_cleanup(curl);

    return response;
}

Response Get(std::string_view url) {
    return PerformRequest(url);
}

Response Post_V1(std::string_view url) {
    return PerformRequest(url, true);
}

Response Post_V2(std::string_view url, std::string_view json) {
    return PerformRequest(
        url, 
        true,
        json, 
        {"Content-Type: application/json"}
    );
}

std::optional<std::string> Response_GetHeaderValue(
    Response& response, std::string_view key
) {
    auto it = response.header.find(std::string(key));
    if (it != response.header.end()) {
        return it->second;
    }
    return std::nullopt;
}

bool Init(sol::state* state) {
    static bool curl_initialized = false;

    if (!curl_initialized) {
        curl_global_init(CURL_GLOBAL_ALL);
        curl_initialized = true;
    }

    (*state)["json"] = state->script(
        std::string(
            __json_lua, 
            __json_lua + __json_lua_len
        )
    ); // json module
    
    state->new_usertype<Response>(
        "Jila_Response",
        "status_code", sol::readonly(&Response::status_code),
        "text", sol::readonly(&Response::text),
        "raw_header", sol::readonly(&Response::raw_header)
    );

    state->set_function(
        "Jila_Response_GetHeaderValue",
        &Response_GetHeaderValue
    );

    state->set_function(
        "Jila_Get",
        &Get
    );

    state->set_function(
        "Jila_Post",
        sol::overload(
            &Post_V1,
            &Post_V2
        )
    );

    return true;
}

void Quit(sol::state* state) {}

}

}
#endif
