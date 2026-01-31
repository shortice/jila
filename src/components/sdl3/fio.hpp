#pragma once
#include "SDL3/SDL_iostream.h"
#include "proxy.hpp"
#include "sol/sol.hpp"

typedef std::shared_ptr<Proxy<SDL_IOStream>> IOStream;

namespace Jila {

void bindSdlFio(sol::state* state);

}
