#pragma once

#include "engine/component.hpp"

namespace Jila {

namespace DataBase_Component {

bool Init(sol::state* state);
void Quit(sol::state* state);

}

static LuaComponent ComponentDataBase {
    "DataBase",
    "Shotice",
    true,
    DataBase_Component::Init,
    DataBase_Component::Quit
};

}
