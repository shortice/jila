#ifdef JILA_IMAGES
#include "components/sdl3/images.hpp"
#include "imgui.h"
#include "SDL3/SDL_render.h"
#include "SDL3_image/SDL_image.h"
#include "misc.hpp"
#include "engine/runtime.hpp"

namespace Jila {

typedef std::shared_ptr<SDL_Texture> Texture;

Texture _SDL_CreateImageTexture(
    std::string_view path
) {
    return MakeSafeMemory<SDL_Texture>(
        IMG_LoadTexture(GetState() -> renderer, path.data()),
        [](SDL_Texture* texture) {
            SDL_DestroyTexture(texture);
        }
    );
}

ImVec2 _SDL_GetTextureSize(Texture texture) {
    ImVec2 vec = ImVec2();

    if (!SDL_GetTextureSize(texture.get(), &vec.x, &vec.y)) {
        vec.x = -1;
        vec.y = -1;
    }

    return vec;
}

void _ImGui_Image(Texture texture, ImVec2& imageSize) {
    ImGui::Image(
        (intptr_t)texture.get(),
        imageSize
    );
}

bool _ImGui_ImageButton_V1(
    std::string_view label,
    Texture texture,
    ImVec2& imageSize
) {
    return ImGui::ImageButton(
        label.data(),
        (intptr_t)texture.get(),
        imageSize
    );
}

void bindSdlImages(sol::state* state) {
    state -> set_function(
        "SDL_CreateImageTexture", &_SDL_CreateImageTexture
    );

    state -> set_function(
        "SDL_GetTextureSize", &_SDL_GetTextureSize
    );

    state -> set_function(
        "Image",
        &_ImGui_Image
    );

    state -> set_function(
        "ImageButton",
        sol::overload(
            &_ImGui_ImageButton_V1
        )
    );
}

}
#endif