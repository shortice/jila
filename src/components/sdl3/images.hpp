#ifdef JILA_IMAGES
#pragma once

#include "sol/sol.hpp"
#include "SDL3/SDL_render.h"

namespace Jila {

typedef std::shared_ptr<SDL_Texture> Texture;

void bindSdlImages(sol::state* state);

}
#endif
