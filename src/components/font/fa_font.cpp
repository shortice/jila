#include "components/font/fa_font.hpp"
#include "components/font/_font.h"

namespace Jila {

namespace FaIconsComponent {

bool Init(sol::state* state) {
    state->script(
        std::string(
            __fa_font_lua, 
            __fa_font_lua + __fa_font_lua_len
        )
    );
    return true;
}

void Quit(sol::state* state) {}

}

}
