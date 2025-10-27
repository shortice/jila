# CLAUDE.md

## Project Overview

Jila is an experimental framework for creating Lua applications built on SDL3 + DearImGui. It's a C++ application that embeds LuaJIT and provides a platform for building cross-platform GUI applications using Lua language.

## Development Commands

### Building the Project

```bash
# Clone with all submodules
git clone <repo> && git submodule update --init --recursive

# Configure CMake (may need to run twice due to leveldb)
cmake ./src -B ./build
cmake ./src -B ./build  # Sometimes needed for leveldb package

# Build the application
cmake --build ./build

# Run example application
./build/main ./examples/sample_app

# Run with custom Lua path
./build/main /path/to/lua/scripts
```

### Development vs Production Builds

**Development builds** (default):
- Hot-reloading enabled via `efsw` file watcher
- Loads Lua files from filesystem
- Slower startup but enables live code changes
- Uses `JILA_RELEASE=OFF` (default)

**Production builds**:
- No hot-reloading
- Embeds Lua code directly in executable
- Faster startup and deployment
- Enable with: `-DJILA_RELEASE=ON`

## Architecture Overview

### Core Architecture
- **Embedded Lua Runtime**: C++ engine embeds LuaJIT for scripting
- **Immediate Mode GUI**: Uses DearImGui for UI development
- **Event-Driven**: SDL3 event system with Lua event handlers
- **Component-Based**: Modular architecture with reusable components

### Key Directories

- `src/engine/`: Core runtime engine and Lua state management
- `src/components/`: Component library providing Lua bindings
- `src/app/`: Application layer and Lua-C++ bridge
- `examples/sample_app/`: Example Lua application structure

### Lua Module System

**Required Module Structure**:
Each Lua module must return a table with:
- `name`: Module identifier
- `Begin()`: Initialization function (called once on load)
- `End()`: Cleanup function (called on application exit)

**Main Module Special Requirements**:
The "main" module additionally requires:
- `BeginMainLoop()`: Called after all modules loaded
- `Render(time)`: Called each frame (time in milliseconds)
- `Event(event)`: Called for SDL events

**Example Module Structure**:
```lua
local M = {}
M.name = "mymodule"

function M.Begin()
    -- Initialize module
end

function M.End()
    -- Cleanup module
end

return M
```

### Development Workflow

1. **Create Lua modules** in the script directory (default: `./app`)
2. **Use hot-reloading** - changes to `.lua` files auto-reload in dev builds
3. **Test in dev mode** first for better error feedback
4. **Build production** for deployment when ready

### Available Components

The framework provides 10 core Lua components:

- **Engine**: Logger, SDL error handling
- **SDL3**: Window, audio, events, images, timers
- **ImGui**: GUI widgets, windows, layout
- **Properties**: Type-safe data binding (IntProperty, FloatProperty, etc.)
- **Threads**: Threading utilities
- **Net**: HTTP client (cpr)
- **Filesystem**: File operations
- **Font**: Font Awesome icons
- **System**: System utilities
- **Database**: LevelDB integration

### Error Handling

- Development builds show detailed Lua error messages via ImGui tooltips
- Check `Jila::Logger` for runtime information
- SDL errors are wrapped with context
- Invalid Lua modules prevent application startup

### Hot Reloading (Development Only)

- Monitors all `.lua` files in the script directory
- Automatically reloads modified modules
- Maintains runtime state across reloads
- Use SDL_EVENT_USER code 1001 to manually trigger reload

### Cross-Platform Support

- Primary platforms: 
* Linux, Android (tested)
* Windows, WASM (need testing and working on compalatibility api)
- Other platforms supported if LuaJIT/SDL3 available
- CCACHE enabled for faster rebuilds
