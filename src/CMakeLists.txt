cmake_minimum_required(VERSION 3.17)
project(Jila LANGUAGES CXX C)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Build type configuration
option(JILA_RELEASE "Compile Lua code and don't use dev tools" OFF)

if(CMAKE_BUILD_TYPE EQUAL "Release")
    set(JILA_RELEASE ON)
endif()

# Set default build type
# TODO: Maybe not use Debug at default build?
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Build type" FORCE)
endif()

# Export compile commands
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Compiler configuration
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    # Common flags for GCC and Clang
    set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
    set(CMAKE_C_FLAGS_DEBUG "-g -O0")
    
    if(JILA_RELEASE)
        set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
        set(CMAKE_C_FLAGS_RELEASE "-O3 -DNDEBUG")
    endif()
    
    # Enable warnings
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wpedantic")
    
    # Ignore unused parameter warnings
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-parameter")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-unused-parameter")
elseif(MSVC)
    # MSVC configuration
    set(CMAKE_CXX_FLAGS_DEBUG "/Zi /Od")
    set(CMAKE_C_FLAGS_DEBUG "/Zi /Od")
    
    if(JILA_RELEASE)
        set(CMAKE_CXX_FLAGS_RELEASE "/O2 /DNDEBUG")
        set(CMAKE_C_FLAGS_RELEASE "/O2 /DNDEBUG")
    endif()
    
    # Enable warnings for MSVC
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /W4")
    
    # Disable unused parameter warnings for MSVC
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4100")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /wd4100")
endif()

# Enable ccache if available
find_program(CCACHE_EXECUTABLE ccache)
if(CCACHE_EXECUTABLE)
    set(CMAKE_CXX_COMPILER_LAUNCHER "${CCACHE_EXECUTABLE}")
    set(CMAKE_C_COMPILER_LAUNCHER "${CCACHE_EXECUTABLE}")
endif()

# Define build-specific macros
if(JILA_RELEASE)
    add_compile_definitions(JILA_RELEASE)
endif()

# Set paths
set(JILA_EXTERNAL_DIR "${CMAKE_SOURCE_DIR}/external")
set(JILA_SOURCE_DIR "${CMAKE_SOURCE_DIR}")
set(JILA_ENGINE_DIR "${JILA_SOURCE_DIR}/engine")
set(JILA_COMPONENTS_DIR "${JILA_SOURCE_DIR}/components")
set(JILA_APP_DIR "${JILA_SOURCE_DIR}/app")

# External dependencies
add_subdirectory(${JILA_EXTERNAL_DIR}/SDL)
add_subdirectory(${JILA_EXTERNAL_DIR}/SDL_Image)
add_subdirectory(${JILA_EXTERNAL_DIR}/SDL_Mixer)
add_subdirectory(${JILA_EXTERNAL_DIR}/lua_jit)

# LevelDB configuration
set(LEVELDB_BUILD_TESTS OFF)
set(LEVELDB_BUILD_BENCHMARKS OFF)
add_subdirectory(${JILA_EXTERNAL_DIR}/leveldb)

# EFSW (only for development builds)
if(NOT JILA_RELEASE)
    add_subdirectory(${JILA_EXTERNAL_DIR}/efsw)
endif()

# Collect source files
set(JILA_IMGUI_SOURCES
    "${JILA_EXTERNAL_DIR}/imgui/imgui.cpp"
    "${JILA_EXTERNAL_DIR}/imgui/imgui_draw.cpp"
    "${JILA_EXTERNAL_DIR}/imgui/imgui_tables.cpp"
    "${JILA_EXTERNAL_DIR}/imgui/imgui_widgets.cpp"
    "${JILA_EXTERNAL_DIR}/imgui/backends/imgui_impl_sdl3.cpp"
    "${JILA_EXTERNAL_DIR}/imgui/backends/imgui_impl_sdlrenderer3.cpp"
    "${JILA_EXTERNAL_DIR}/imgui/imgui_demo.cpp"
)

# Collect library sources
file(GLOB_RECURSE JILA_LIB_SOURCES
    "${JILA_ENGINE_DIR}/*.cpp"
    "${JILA_COMPONENTS_DIR}/**/*.cpp"
)

# Add application source for release builds
if(JILA_RELEASE)
    # TODO: need execute script for .lua files to one .cpp
    # or maybe other? Like .res file contains all code? I need think.
    list(APPEND JILA_LIB_SOURCES "${JILA_APP_DIR}/jila_app.cpp")
endif()

# Create target
if(ANDROID)
    add_library(main SHARED
        "${JILA_SOURCE_DIR}/main.cpp"
        "${JILA_SOURCE_DIR}/external/ulog.c"
        ${JILA_LIB_SOURCES}
        ${JILA_IMGUI_SOURCES}
    )
else()
    add_executable(main
        "${JILA_SOURCE_DIR}/main.cpp"
        "${JILA_SOURCE_DIR}/external/ulog.c"
        ${JILA_LIB_SOURCES}
        ${JILA_IMGUI_SOURCES}
    )
endif()

# Target properties
set_target_properties(main PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

# Platform-specific properties
if(WIN32)
    set_target_properties(main PROPERTIES WIN32_EXECUTABLE TRUE)
endif()

if(EMSCRIPTEN)
    set_target_properties(main PROPERTIES SUFFIX ".html")
endif()

# Link libraries
target_link_libraries(main
    PRIVATE
    $<TARGET_NAME_IF_EXISTS:SDL3::SDL3main>
    $<IF:$<TARGET_EXISTS:SDL3::SDL3>,SDL3::SDL3,SDL3::SDL3-static>
    $<IF:$<TARGET_EXISTS:SDL3_image::SDL3_image>,SDL3_image::SDL3_image,SDL3_image::SDL3_image-static>
    $<IF:$<TARGET_EXISTS:SDL3_mixer::SDL3_mixer>,SDL3_mixer::SDL3_mixer,SDL3_mixer::SDL3_mixer-static>
)

# FetchContent dependencies
include(FetchContent)

# Android curl configuration
if(ANDROID)
    # TODO: Fix curl build for Android. SSL dont work.
    find_package(curl REQUIRED CONFIG COMPONENTS HTTP HTTPS)
    target_link_libraries(main PRIVATE curl::curl_static)
endif()

# CPR HTTP library
FetchContent_Declare(
    cpr
    GIT_REPOSITORY https://github.com/libcpr/cpr.git
    GIT_TAG 1.12.0
)
FetchContent_MakeAvailable(cpr)

# Final linking
target_link_libraries(main
    PRIVATE
    luajit::lib
    luajit::header
    cpr::cpr
    leveldb
)

if(NOT JILA_RELEASE)
    target_link_libraries(main PRIVATE efsw)
endif()

# Include directories
target_include_directories(main PRIVATE
    ${JILA_EXTERNAL_DIR}
    ${JILA_EXTERNAL_DIR}/imgui
    ${JILA_EXTERNAL_DIR}/imgui/backends
    ${JILA_SOURCE_DIR}
    ${JILA_EXTERNAL_DIR}/efsw/include
)
