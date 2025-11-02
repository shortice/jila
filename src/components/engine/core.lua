---@meta core

--- Get error, else "".
---
--- If you see this message on some functions:
--- 
--- "See: SDL_GetError for read error."
--- 
--- Then function supports set's error when failing.
--- 
--- @return string
function SDL_GetError() end

--- Get module, else nil.
--- @param name string Module name.
--- @return table?
function GetModule(name) end

--- Global variables for storing some data across modules.
--- Careful! This not work in separate thread's.
---
--- @type table
Scope = {}
