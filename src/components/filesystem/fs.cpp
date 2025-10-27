#include <filesystem>
#include "components/filesystem/fs.hpp"
#include "SDL3/SDL_filesystem.h"
#include "sol/sol.hpp"
#ifdef __ANDROID__
#include "components/system/jila_android.hpp"
#endif

using namespace std::filesystem;

namespace Jila {

namespace FileSystemComponent {

struct FsEntry {
    std::string path;
    std::string name;
    std::string ext;
    bool isDir;
};

struct FsState {
    FsState(std::string currentCwd) : 
        currentCwd(currentCwd), 
        includeHidden(false) {}

    std::vector<FsEntry> currentEntries;
    std::string currentCwd;
    bool includeHidden;
};

void Fs_GetFolders(FsState& state) {
    state.currentEntries.clear();
    std::string filename;
    std::string ext;

    for (const directory_entry& _ : 
        directory_iterator(state.currentCwd)
    ) {
        try {
            if (_.status().type() != file_type::directory) continue;
        } catch (std::exception&) {
            continue;
        }

        bool isHidden = (
            _.path()
            .filename()
            .string()
            .find_first_of(".") == 0
        );

        if (!state.includeHidden and isHidden) continue;

        if (_.path().has_filename()) {
            filename = _.path().filename();
        } else {
            filename = "";
        }

        if (_.path().has_extension()) {
            ext = _.path().extension();
        } else {
            ext = "";
        }

        state.currentEntries.push_back({
            _.path(),
            filename,
            ext,
            _.is_directory()
        });
    }
}

template<typename T>
void _IterFiles(
    FsState& state, 
    std::vector<std::string>& exts
) {
    std::string filename;
    std::string ext;

    for (const directory_entry& _ : 
        T(state.currentCwd)
    ) {
        try {
            if (_.status().type() != file_type::regular) continue;
        } catch (std::exception&) {
            continue;
        }

        bool isHidden = (
            _.path()
            .filename()
            .string()
            .find_first_of(".") == 0
        );

        if (!state.includeHidden and isHidden) continue;

        if (
            std::find(
                exts.begin(), exts.end(), _.path().extension()
            ) == exts.end()
            and !exts.empty()
        ) continue;

        if (_.path().has_filename()) {
            filename = _.path().filename();
        } else {
            filename = "";
        }

        if (_.path().has_extension()) {
            ext = _.path().extension();
        } else {
            ext = "";
        }

        state.currentEntries.push_back({
            _.path(),
            filename,
            ext,
            _.is_directory()
        });
    }
}

void Fs_GetAllFiles(
    FsState& state,
    bool recursive,
    std::vector<std::string> exts
) {
    state.currentEntries.clear();

    if (recursive) {
        _IterFiles<recursive_directory_iterator>(
            state,
            exts
        );
    } else {
        _IterFiles<directory_iterator>(
            state,
            exts
        );
    }
}

std::string Fs_GetHomePath() {
    #ifndef __ANDROID__
    return SDL_GetUserFolder(SDL_FOLDER_HOME);
    #else
    return android_getExternalStoragePath();
    #endif
}

bool Init(sol::state* state) {
    state->new_usertype<FsEntry>(
        "FsEntry",
        "path", &FsEntry::path,
        "name", &FsEntry::name,
        "ext", &FsEntry::ext,
        "isDir", &FsEntry::isDir
    );

    state->new_usertype<FsState>(
        "FsState",
        sol::constructors<FsState(std::string)>(),
        "currentEntries", &FsState::currentEntries,
        "currentCwd", &FsState::currentCwd,
        "includeHidden", &FsState::includeHidden
    );

    state->set_function(
        "Fs_GetFolders",
        &Fs_GetFolders
    );

    state->set_function(
        "Fs_GetAllFiles",
        sol::overload(
            [](FsState& state, bool recursive) {
                return Fs_GetAllFiles(state, recursive, {});
            },
            [](
                FsState& state, 
                bool recursive, 
                std::vector<std::string> exts
            ) {
                return Fs_GetAllFiles(
                    state,
                    recursive,
                    exts
                );
            }
        )
    );

    state->set_function(
        "Fs_GetHomePath",
        &Fs_GetHomePath
    );

    return true;
}

void Quit(sol::state* state) {

}

}

}
