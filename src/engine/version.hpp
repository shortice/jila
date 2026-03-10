/*
Version
*/
#pragma once

/*
2026030001
2026 - year of the library path
03 - month of the library path
0001 - current commit number
*/
#define JILA_VERSION 2026030088

namespace Jila {

constexpr unsigned int getCompiledVersion();

#define JILA_COMPILED_VERSION getCompiledVersion()

}
