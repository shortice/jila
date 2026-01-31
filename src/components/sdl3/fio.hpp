#pragma once
#include "SDL3/SDL_iostream.h"
#include "sol/sol.hpp"

typedef std::shared_ptr<SDL_IOStream> IOStream;

namespace Jila {

void bindSdlFio(sol::state* state);

}
