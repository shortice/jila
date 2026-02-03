#pragma once
#include "engine/component.hpp"

namespace Jila {

namespace FileSystemComponent {

bool Init(sol::state* state);
void Quit(sol::state* state);

}

/*
A function for getting a internal path of the Application.

This is safe place for writing/reading files.
The returned path is guaranteed to end with a path separator 
('\' on Windows, '/' on most other platforms).
*/
std::string Fs_GetPrefPath(std::string_view org, std::string_view name);

/*
A function for getting a path to the application data directory.

On android please do not use this function for getting assets files path, instead
just use path like this "test.png" for opening file "test.png" in the assets
directory inside .apk.
*/
std::string Fs_GetBasePath();

static LuaComponent ComponentFileSystem {
    "FileSystem",
    "Shortice",
    FileSystemComponent::Init,
    FileSystemComponent::Quit
};

}
