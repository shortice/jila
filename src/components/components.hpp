#pragma once

#include <array>
#include "engine/component.hpp"

#include "components/engine/c_engine.hpp"
#include "components/properties/c_properties.hpp"
#include "components/imgui/c_imgui.hpp"
#include "components/threads/c_threads.hpp"
#include "components/sdl3/c_sdl3.hpp"
#include "components/net/c_net.hpp"
#include "components/filesystem/fs.hpp"
#include "components/font/fa_font.hpp"
#include "components/system/c_system.hpp"
#include "components/database/c_database.hpp"

namespace Jila {

static std::array<LuaComponent, 10> components {
    ComponentEngine,
    ComponentProperties,
    ComponentImGui,
    ComponentThreads,
    ComponentSdl,
    ComponentNet,
    ComponentFileSystem,
    ComponentFaIcons,
    ComponentSystem,
    ComponentDataBase
};

}
