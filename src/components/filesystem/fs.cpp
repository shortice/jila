#include <filesystem>
#include <algorithm>
#include "components/filesystem/fs.hpp"
#include "SDL3/SDL_filesystem.h"
#include "SDL3/SDL_system.h"
#include "sol/sol.hpp"
#ifdef __ANDROID__
#include "jila-android.hpp"
#endif
#include "tracy/Tracy.hpp"

// TODO: Android port

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

// TODO: Android?
void Fs_GetFolders(FsState& state) {
    ZoneScoped;
    state.currentEntries.clear();
    std::string filename;
    std::string ext;

    for (const directory_entry& _ : 
        directory_iterator(state.currentCwd)
    ) {
        try {
            if (_.status().type() != file_type::directory) continue;
        } catch (std::exception&) {
            // TODO: we really need handle errors in this lines?
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
            filename = _.path().filename().string();
        }

        if (_.path().has_extension()) {
            ext = _.path().extension().string();
        }

        state.currentEntries.push_back({
            _.path().string(),
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
    ZoneScoped;
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
            filename = _.path().filename().string();
        }

        if (_.path().has_extension()) {
            ext = _.path().extension().string();
        }

        state.currentEntries.push_back({
            _.path().string(),
            filename,
            ext,
            _.is_directory()
        });
    }
}

#ifdef __ANDROID__
void Fs_GetAllFilesAndroid(
    FsState& state,
    const char** paths,
    std::vector<std::string>& exts
) {
    ZoneScoped;
    while (*paths) {
        std::string_view path = *paths;
        paths++;

        size_t ext_start_pos = path.find_last_of(".");
        size_t name_start_pos = path.find_last_of("/");
        std::string file_ext;

        if (ext_start_pos != path.npos) {
            // https://en.cppreference.com/w/cpp/string/basic_string/find_last_of
            file_ext = {
                path.begin() + ext_start_pos,
                path.end()
            };
        }
        else {
            file_ext = "";
        }

        std::string_view file_name = {
            path.begin() + name_start_pos,
            path.begin() + ext_start_pos
        };

        if (exts.size() != 0 && file_ext != "") {
            const auto& _ = std::find(exts.begin(), exts.end(), file_ext);
            if (_ == exts.end()) continue;
        };

        // TODO: Iter dirs on Android? Maybe
        state.currentEntries.push_back({
            path.data(), file_name.data(),
            file_ext, false
        });
    }
}
#endif

void Fs_GetAllFiles(
    FsState& state,
    bool recursive,
    std::vector<std::string> exts
) {
    ZoneScoped;
    state.currentEntries.clear();

    #ifndef __ANDROID__
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
    #else
    const char** paths = Jila_Android_IterateFiles(
        state.currentCwd.c_str(),
        recursive
    );

    Fs_GetAllFilesAndroid(state, paths, exts);

    free(paths);
    #endif
}

static std::string _pref_Path;

std::string Fs_GetPrefPath(std::string_view org, std::string_view name) {
    ZoneScoped;
    if (_pref_Path.empty()) {
        const char* pref_path = SDL_GetPrefPath(org.data(), name.data());
        _pref_Path = pref_path;
        SDL_free((void*)pref_path);
    };

    return _pref_Path;
}

std::string Fs_GetBasePath() {
    ZoneScoped;
    #ifndef __ANDROID__
    return SDL_GetBasePath();
    #else
    return "";
    #endif
}

bool Init(sol::state* state) {
    state->new_usertype<FsEntry>(
        "Jila_FsEntry",
        "path", &FsEntry::path,
        "name", sol::readonly(&FsEntry::name),
        "ext", sol::readonly(&FsEntry::ext),
        "isDir", sol::readonly(&FsEntry::isDir)
    );

    state->set_function(
        "Jila_Create_FS_State", 
        [](std::string currentCwd) { 
            return FsState(currentCwd); 
        }
    );

    state->new_usertype<FsState>(
        "Jila_FsState",
        "currentEntries", sol::readonly(&FsState::currentEntries),
        "currentCwd", &FsState::currentCwd,
        "includeHidden", &FsState::includeHidden
    );

    state->set_function(
        "Jila_Fs_GetFolders",
        &Fs_GetFolders
    );

    state->set_function(
        "Jila_Fs_GetAllFiles",
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
        "Jila_Fs_GetPrefPath",
        &Fs_GetPrefPath
    );

    state->set_function(
        "Jila_Fs_GetBasePath",
        &Fs_GetBasePath
    );

    return true;
}

void Quit(sol::state* state) {

}

}

}
