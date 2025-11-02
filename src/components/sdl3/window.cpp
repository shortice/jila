#include "components/sdl3/window.hpp"
#include "engine/runtime.hpp"

namespace Jila {

void bindSdlWindow(sol::state* state) {
    // SDL_SetWindowTitle
    state -> set_function(
        "SDL_SetWindowTitle",
        [](std::string_view title) -> bool {
            return SDL_SetWindowTitle(
                GetState() -> window, title.data()
            );
        }
    );

    // SDL_GetWindowSize
    state -> set_function(
        "SDL_GetWindowSize",
        []() -> ImVec2 {
            int w = 0, h = 0;
            SDL_GetWindowSize(GetState() -> window, &w, &h);
            return ImVec2(w, h);
        }
    );

    state -> set_function(
        "SDL_GetWindowSafeArea",
        []() -> ImVec4 {
            SDL_Rect rect {0, 0, 0, 0};
            SDL_GetWindowSafeArea(GetState() -> window, &rect);
            return ImVec4(rect.x, rect.y, rect.h, rect.w);
        }
    );

    // SDL_SetWindowSize
    state -> set_function(
        "SDL_SetWindowSize",
        [](ImVec2 size) -> bool {
            return SDL_SetWindowSize(GetState() -> window, size.x, size.y);
        }
    );
}



}
