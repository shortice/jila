#ifdef JILA_IMAGES
#include "components/sdl3/images.hpp"
#include "SDL3_image/SDL_image.h"
#include "misc.hpp"
#include "engine/runtime.hpp"

namespace Jila {

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

void bindSdlImages(sol::state* state) {
    state -> set_function(
        "Jila_CreateImageTexture", &_SDL_CreateImageTexture
    );

    state -> set_function(
        "Jila_GetTextureSize", &_SDL_GetTextureSize
    );
}

}
#endif
