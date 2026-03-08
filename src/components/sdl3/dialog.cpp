#include "components/sdl3/dialog.hpp"
#include "SDL3/SDL_dialog.h"
#include "SDL3/SDL_events.h"
#include "engine/runtime.hpp"
#include "engine/logger.hpp"
#include "tracy/Tracy.hpp"

#ifdef __ANDROID__
#include "jila-android.hpp"
#endif

namespace Jila {

void _PushDialogEvent(SDL_DialogState* state) {
    ZoneScoped;
    SDL_Event event;

    event.type = SDL_EVENT_USER;
    event.user.code = 1005;
    event.user.data1 = state;

    SDL_PushEvent(&event);
}

void _SDL_OpenFileDialogCallback(
    void* userdata,
    const char* const* filelist,
    int filter
) {
    ZoneScoped;
    SDL_DialogState* state = new SDL_DialogState();

    state->is_folder = false;

    if (filelist) {
        for (int i = 0; filelist[i] != nullptr; i++) {
            state->selected_files.push_back(filelist[i]);
        }
    }

    _PushDialogEvent(state);
}

void _SDL_OpenFolderDialogCallback(void* userdata, const char* const* filelist, int filter) {
    ZoneScoped;
    SDL_DialogState* state = new SDL_DialogState();
    state->is_folder = true;

    if (filelist && filelist[0]) {
        state->selected_folder = filelist[0];
    }

    _PushDialogEvent(state);
}

#ifdef __ANDROID__
void _Android_OpenFolderCallback(const char* folder_uri) {
    ZoneScoped;
    SDL_DialogState* state = new SDL_DialogState();
    state->is_folder = true;

    if (folder_uri) {
        state->selected_folder = folder_uri;
    } else {
        state->selected_folder = "";
    }

    _PushDialogEvent(state);
}
#endif

void SDL_OpenFileDialog(const std::vector<std::string>& allow_extensions) {
    ZoneScoped;
    std::string patterns;

    for (size_t i = 0; i < allow_extensions.size(); ++i) {
        patterns += allow_extensions[i];
        if (i < allow_extensions.size() - 1) {
            patterns += ";";
        }
    }

    SDL_DialogFileFilter filter = { 
        "Files", patterns.c_str() 
    };

    int nfilters;

    if (allow_extensions.empty()) {
        nfilters = 0;
    } else {
        nfilters = 1;
    }

    SDL_ShowOpenFileDialog(
        &_SDL_OpenFileDialogCallback,
        nullptr, GetState()->window,
        &filter, nfilters, 
        nullptr, true
    );
}

void _SDL_OpenFolderDialog() {
    ZoneScoped;
    #ifdef __ANDROID__
    Jila_Android_OpenFolder(&_Android_OpenFolderCallback);
    #else
    SDL_ShowOpenFolderDialog(
        &_SDL_OpenFolderDialogCallback, nullptr,
        GetState()->window, nullptr,
        false
    );
    #endif
}

void _SDL_OpenFileDialog() {
    ZoneScoped;
    SDL_OpenFileDialog({});
}

void _SDL_OpenFileDialog_V2(std::vector<std::string> extensions) { 
    ZoneScoped;
    SDL_OpenFileDialog(extensions);
}

SDL_DialogState _SDL_GetDialogState(SDL_UserEvent& event) {
    ZoneScoped;
    return *(SDL_DialogState*)event.data1;
}

void bindSdlDialog(sol::state* state) {
    state->new_usertype<SDL_DialogState>("Jila_DialogState",
        "is_folder", &SDL_DialogState::is_folder,
        "selected_files", &SDL_DialogState::selected_files,
        "selected_folder", &SDL_DialogState::selected_folder
    );

    state->set_function("Jila_OpenFileDialog", sol::overload(
        &_SDL_OpenFileDialog,
        &_SDL_OpenFileDialog_V2
    ));

    state->set_function("Jila_OpenFolderDialog", &_SDL_OpenFolderDialog);
    state->set_function("Jila_GetDialogState", &_SDL_GetDialogState);
}

}
