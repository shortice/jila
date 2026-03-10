#include "engine/bundle.hpp"
#include "zip.h"
#include "SDL3/SDL_iostream.h"

namespace Jila {

struct buffer_t {
    char *data;
    size_t size;
};

static size_t on_extract(
    void *arg, 
    unsigned long long offset, 
    const void *data, size_t size
) {
    struct buffer_t *buf = (struct buffer_t *)arg;
    buf->data = (char*)realloc(
        buf->data, buf->size + size + 1
    );

    memcpy(&(buf->data[buf->size]), data, size);
    buf->size += size;
    buf->data[buf->size] = 0;

    return size;
}

// NOTE: error handling and throw (via SDL_SetError?)
std::string openEntry(zip_t* zip, const char* path) {
    std::string result;
    struct buffer_t buf = {0};

    zip_entry_open(zip, path);
    zip_entry_extract(zip, &on_extract, &buf);
    zip_entry_close(zip);

    result = buf.data;

    free(buf.data);

    return result;
}

LuaBundle bundleError(const char* error) {
    LuaBundle errorBundle;
    errorBundle.hasError = true;
    errorBundle.error = error;

    return errorBundle;
}

LuaBundle BundleUnpack(const char* path) {
    SDL_IOStream* stream = SDL_IOFromFile(path, "r");

    if (!stream) return bundleError(SDL_GetError());

    size_t streamSize = SDL_GetIOSize(stream) * sizeof(char);

    if (streamSize < 0) {
        SDL_CloseIO(stream);
        return bundleError(SDL_GetError());
    }

    char* data = (char*)malloc(streamSize);

    if (SDL_ReadIO(stream, (void*)data, streamSize) == 0) {
        SDL_CloseIO(stream);
        return bundleError(SDL_GetError());
    }

    zip_t* bundle = zip_stream_open(data, streamSize, 0, 'r');

    if (!bundle) {
        SDL_CloseIO(stream);
        return bundleError("Open .zip failed");
    }

    std::vector<std::string> luaCode;
    std::string jilaVersion = openEntry(bundle, "JILA_VERSION"); // required core version
    std::string version = openEntry(bundle, "VERSION"); // bundle version
    std::string name = openEntry(bundle, "NAME"); // name
    std::string author = openEntry(bundle, "AUTHOR"); // author
    std::string hash = openEntry(bundle, "HASH"); // bundle (.lua files) hash

    int i, n = zip_entries_total(bundle);

    for (i = 0; i < n; ++i) {
        zip_entry_openbyindex(bundle, i);
    
        std::string entryName = zip_entry_name(bundle);
        int isDir = zip_entry_isdir(bundle);
    
        zip_entry_close(bundle);

        if (isDir == 0 && entryName.ends_with(".lua")) {
            luaCode.push_back(openEntry(bundle, entryName.c_str()));
        }
    }

    zip_close(bundle);

    // TODO: HASH logic, improve errors handling and version handling.
    // But in my own purposes its okay. Maybe..

    return LuaBundle {
        false,
        "",
        luaCode,
        std::stoi(jilaVersion),
        std::stoi(version),
        name,
        author,
        hash
    };
}

}
