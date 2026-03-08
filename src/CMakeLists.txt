cmake_minimum_required(VERSION 3.17)
project(Jila LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Build type configuration
option(JILA_RELEASE "Compile Lua code and don't use dev tools" OFF)
option(JILA_AUDIO "Enable audio module" OFF)
option(JILA_IMAGES "Enable image module" OFF)
option(JILA_NET "Enable Net module" OFF)
option(JILA_DATABASE "Enable database module" OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/app)

option(JILA_ALL "Enable all modules" OFF)
# For lint/static-analyze/etc

if(JILA_ALL)
    set(JILA_AUDIO ON)
    set(JILA_IMAGES ON)
    set(JILA_NET ON)
    set(JILA_DATABASE ON)
endif()

# TODO: Enable if i develop bundles, similar to React Native
#if(CMAKE_BUILD_TYPE STREQUAL "Release")
#    set(JILA_RELEASE ON)
#endif()

# Set default build type
# TODO: Maybe not use Debug at default build?
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Build type" FORCE)
endif()

# Export compile commands
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Enable ccache if available
find_program(CCACHE_EXECUTABLE ccache)
if(CCACHE_EXECUTABLE)
    set(CMAKE_CXX_COMPILER_LAUNCHER "${CCACHE_EXECUTABLE}")
    set(CMAKE_C_COMPILER_LAUNCHER "${CCACHE_EXECUTABLE}")
endif()

# Set paths
set(JILA_EXTERNAL_DIR "${CMAKE_SOURCE_DIR}/external")
set(JILA_SOURCE_DIR "${CMAKE_SOURCE_DIR}")
set(JILA_ENGINE_DIR "${JILA_SOURCE_DIR}/engine")
set(JILA_COMPONENTS_DIR "${JILA_SOURCE_DIR}/components")
set(JILA_APP_DIR "${JILA_SOURCE_DIR}/app")

# Collect source files
set(JILA_IMGUI_SOURCES
    "${JILA_EXTERNAL_DIR}/imgui/imgui.cpp"
    "${JILA_EXTERNAL_DIR}/imgui/imgui_draw.cpp"
    "${JILA_EXTERNAL_DIR}/imgui/imgui_tables.cpp"
    "${JILA_EXTERNAL_DIR}/imgui/imgui_widgets.cpp"
    "${JILA_EXTERNAL_DIR}/imgui/misc/cpp/imgui_stdlib.cpp"
    "${JILA_EXTERNAL_DIR}/imgui/backends/imgui_impl_sdl3.cpp"
    "${JILA_EXTERNAL_DIR}/imgui/backends/imgui_impl_sdlrenderer3.cpp"
    "${JILA_EXTERNAL_DIR}/imgui/imgui_demo.cpp"
)

# Collect Lua sources
file(GLOB JILA_LUA_SOURCES "${JILA_EXTERNAL_DIR}/lua/*.c")
list(REMOVE_ITEM JILA_LUA_SOURCES
    "${JILA_EXTERNAL_DIR}/lua/lua.c"
    "${JILA_EXTERNAL_DIR}/lua/luac.c"
    "${JILA_EXTERNAL_DIR}/lua/onelua.c"
    "${JILA_EXTERNAL_DIR}/lua/ltests.c"
)

add_library(lua STATIC ${JILA_LUA_SOURCES})
target_include_directories(lua PUBLIC "${JILA_EXTERNAL_DIR}/lua")

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

if(JILA_DATABASE)
    list(APPEND JILA_LIB_SOURCES "${JILA_EXTERNAL_DIR}/sqlite3/sqlite3.c")
endif()

# Create target
if(ANDROID)
    add_library(main SHARED
        "${JILA_SOURCE_DIR}/main.cpp"
        "${JILA_SOURCE_DIR}/misc.cpp"
        "${JILA_SOURCE_DIR}/external/ulog.c"
        ${JILA_LIB_SOURCES}
        ${JILA_IMGUI_SOURCES}
    )
else()
    add_executable(main
        "${JILA_SOURCE_DIR}/main.cpp"
        "${JILA_SOURCE_DIR}/misc.cpp"
        "${JILA_SOURCE_DIR}/external/ulog.c"
        ${JILA_LIB_SOURCES}
        ${JILA_IMGUI_SOURCES}
    )
endif()

# Compiler configuration
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(main PRIVATE -Wno-unused-parameter -Wno-newline-eof)
else()
    message(FATAL_ERROR "Unsupported compiler.")
endif()

option(TRACY_ENABLE "" ON)
option(TRACY_ON_DEMAND "" ON)
add_subdirectory(${JILA_EXTERNAL_DIR}/tracy)
target_link_libraries(main PUBLIC Tracy::TracyClient)

add_subdirectory(${JILA_EXTERNAL_DIR}/SDL)

# Define build-specific macros
if(JILA_RELEASE)
    target_compile_definitions(main PRIVATE JILA_RELEASE)
endif()

if(JILA_IMAGES)
    add_subdirectory(${JILA_EXTERNAL_DIR}/SDL_Image)
    target_compile_definitions(main PRIVATE JILA_IMAGES)
endif()

if(JILA_AUDIO)
    add_subdirectory(${JILA_EXTERNAL_DIR}/SDL_Mixer)
    target_compile_definitions(main PRIVATE JILA_AUDIO)
endif()

# EFSW (only for development builds)
if(NOT JILA_RELEASE)
    add_subdirectory(${JILA_EXTERNAL_DIR}/efsw)
endif()

# Platform-specific properties
if(WIN32 AND JILA_RELEASE)
    set_target_properties(main PROPERTIES WIN32_EXECUTABLE TRUE)
endif()

if(ANDROID)
    find_package(jila-android REQUIRED CONFIG)
    target_link_libraries(main PRIVATE jila-android::jila-android)
endif()

# Link libraries
target_link_libraries(main
    PRIVATE
    lua
    $<TARGET_NAME_IF_EXISTS:SDL3::SDL3main>
    $<IF:$<TARGET_EXISTS:SDL3::SDL3>,SDL3::SDL3,SDL3::SDL3-static>
)

if(JILA_IMAGES)
    target_link_libraries(
        main 
        PRIVATE
        $<IF:$<TARGET_EXISTS:SDL3_image::SDL3_image>,SDL3_image::SDL3_image,SDL3_image::SDL3_image-static>
    )
endif()

if(JILA_AUDIO)
    target_link_libraries(
        main 
        PRIVATE
        $<IF:$<TARGET_EXISTS:SDL3_mixer::SDL3_mixer>,SDL3_mixer::SDL3_mixer,SDL3_mixer::SDL3_mixer-static>
    )
endif()

if(JILA_NET)
    set(CURL_USE_LIBPSL OFF)

    if(WIN32)
        set(CURL_USE_SCHANNEL ON)
    endif()

    if(ANDROID)
        find_package(curl REQUIRED CONFIG)
        target_link_libraries(main PRIVATE curl::curl_static)
    else()
        add_subdirectory(${JILA_EXTERNAL_DIR}/curl)
        target_link_libraries(main PRIVATE CURL::libcurl)
    endif()

    target_compile_definitions(main PRIVATE JILA_NET)
endif()

if(JILA_DATABASE)
    target_compile_definitions(main PRIVATE JILA_DATABASE)
endif()

if(NOT JILA_RELEASE)
    target_link_libraries(main PRIVATE efsw)
endif()

# Include directories
target_include_directories(main PRIVATE
    ${JILA_EXTERNAL_DIR}
    ${JILA_EXTERNAL_DIR}/imgui
    ${JILA_EXTERNAL_DIR}/imgui/backends
    ${JILA_EXTERNAL_DIR}/imgui/misc/cpp/
    ${JILA_SOURCE_DIR}
    ${JILA_EXTERNAL_DIR}/efsw/include
)
