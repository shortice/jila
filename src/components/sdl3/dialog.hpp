#pragma once
#include "sol/sol.hpp"
#include "SDL3/SDL_events.h"
#include <vector>
#include <string>

namespace Jila {

struct SDL_DialogState {
    bool is_folder;
    std::vector<std::string> selected_files;
    std::string selected_folder;
};

void SDL_OpenFileDialog(
    const std::vector<std::string>& allow_extensions
);

void SDL_OpenFolderDialog();

SDL_DialogState SDL_GetDialogState(SDL_UserEvent& event);

void bindSdlDialog(sol::state* state);

}
