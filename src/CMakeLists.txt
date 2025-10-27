cmake_minimum_required(VERSION 3.17)
project(Jila LANGUAGES CXX C)

option(JILA_RELEASE "Compile Lua code and don't use dev tools." OFF)

set(CMAKE_BUILD_TYPE Debug)

# Add debug flags for GCC and Clang
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g")
endif()

# Add debug flags for MSVC
if(MSVC)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Zi")
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} /Zi")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_program(CCACHE_EXECUTABLE ccache)

if(CCACHE_EXECUTABLE)
    set(CMAKE_CXX_COMPILER_LAUNCHER ccache)
    set(CMAKE_C_COMPILER_LAUNCHER ccache)
endif()

if(JILA_RELEASE)
    add_compile_definitions(JILA_RELEASE)
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(DEP ${CMAKE_SOURCE_DIR}/external)

# Библы
add_subdirectory(${DEP}/SDL)
add_subdirectory(${DEP}/SDL_Image)
add_subdirectory(${DEP}/SDL_Mixer)
add_subdirectory(${DEP}/lua_jit)

set(LEVELDB_BUILD_TESTS OFF)
set(LEVELDB_BUILD_BENCHMARKS OFF)
add_subdirectory(${DEP}/leveldb)

if(JILA_RELEASE STREQUAL "OFF")
    add_subdirectory(${DEP}/efsw) # TODO: only on DEV build
endif()

set(imgui_source
    ${DEP}/imgui/imgui.cpp
    ${DEP}/imgui/imgui_draw.cpp
    ${DEP}/imgui/imgui_tables.cpp
    ${DEP}/imgui/imgui_widgets.cpp
    ${DEP}/imgui/backends/imgui_impl_sdl3.cpp
    ${DEP}/imgui/backends/imgui_impl_sdlrenderer3.cpp
    ${DEP}/imgui/imgui_demo.cpp
)

file(GLOB lib_sources
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/engine/*.cpp
    ${CMAKE_SOURCE_DIR}/components/**/*.cpp
)

set(lib_sources ${lib_sources}
    ${CMAKE_SOURCE_DIR}/misc.cpp
)

if(JILA_RELEASE)
    set(lib_sources
        ${lib_sources}
        ${CMAKE_SOURCE_DIR}/app/jila_app.cpp
    )
endif()

if(ANDROID)
    add_library(main
        ${CMAKE_SOURCE_DIR}/main.cpp
        ${CMAKE_SOURCE_DIR}/external/ulog.c
        ${lib_sources} ${imgui_source}
    )
else()
    add_executable(main
        ${CMAKE_SOURCE_DIR}/main.cpp
        ${CMAKE_SOURCE_DIR}/external/ulog.c
        ${lib_sources} ${imgui_source}
    )
endif()

target_link_libraries(main
    PRIVATE
    $<TARGET_NAME_IF_EXISTS:SDL3::SDL3main>
    $<IF:$<TARGET_EXISTS:SDL3::SDL3>,SDL3::SDL3,SDL3::SDL3-static>
)

target_link_libraries(main PRIVATE $<IF:$<TARGET_EXISTS:SDL3_image::SDL3_image>,SDL3_image::SDL3_image,SDL3_image::SDL3_image-static>)

target_link_libraries(main PRIVATE $<IF:$<TARGET_EXISTS:SDL3_mixer::SDL3_mixer>,SDL3_mixer::SDL3_mixer,SDL3_mixer::SDL3_mixer-static>)

include(FetchContent)

if(ANDROID) # TODO: Fix curl build for Android. SSL dont work.
    find_package(curl REQUIRED CONFIG COMPONENTS HTTP HTTPS)
    target_link_libraries(main PRIVATE curl::curl_static)
endif()

FetchContent_Declare(
    cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git
    GIT_TAG 1.12.0
)
FetchContent_MakeAvailable(cpr)

target_link_libraries(
    main
    PRIVATE luajit::lib luajit::header cpr::cpr leveldb
)

if(JILA_RELEASE STREQUAL "OFF")
    target_link_libraries(
        main
        PRIVATE efsw
    )
endif()

target_include_directories(
    main PRIVATE
    ${DEP}
    ${DEP}/imgui
    ${DEP}/imgui/backends
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${DEP}/efsw/include
)

set_property(TARGET main PROPERTY WIN32_EXECUTABLE TRUE)

if(EMSCRIPTEN)
    # Create a html webpage
    set_property(TARGET main PROPERTY SUFFIX ".html")
endif()
