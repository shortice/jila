#pragma once

#include <vector>
#include "engine/component.hpp"

#include "components/engine/c_engine.hpp"
#include "components/properties/c_properties.hpp"
#include "components/imgui/c_imgui.hpp"
#include "components/threads/c_threads.hpp"
#include "components/sdl3/c_sdl3.hpp"
#ifdef JILA_NET
#include "components/net/c_net.hpp"
#endif
#include "components/filesystem/fs.hpp"
#include "components/font/fa_font.hpp"
#include "components/system/c_system.hpp"
#ifdef JILA_DATABASE
#include "components/database/c_database.hpp"
#endif

namespace Jila {

static std::vector<LuaComponent> components {
    ComponentEngine,
    ComponentProperties,
    ComponentImGui,
    ComponentThreads,
    ComponentSdl,
    #ifdef JILA_NET
    ComponentNet,
    #endif
    ComponentFileSystem,
    ComponentFaIcons,
    ComponentSystem,
    #ifdef JILA_DATABASE
    ComponentDataBase
    #endif
};

}
