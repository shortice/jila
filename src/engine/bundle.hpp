/*
Lua code bundle loader.

Bundle is a concept representing .zip archive contains:
1) Compiled lua bytecode;
2) Metadata such as required jila version, bundle name (app name), author,
bundle hash and version;
*/
#pragma once

#include <string>
#include <vector>

namespace Jila {

struct LuaBundle {
    bool hasError;
    std::string error;

    std::vector<std::string> luaCode;
    int jilaVersionRequiredMin;
    int bundleVersion;
    std::string name;
    std::string author;
    std::string bundleHash;
};

/*
Load the .bundle (.zip) file.

Returns the LuaBundle struct.
*/
LuaBundle BundleUnpack(const char* path);

}
