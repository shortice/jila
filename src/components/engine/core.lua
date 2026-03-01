---@meta core

--- Get error, else "".
---
--- If you see this message on some functions:
--- 
--- "See: Jila_GetError for read error."
--- 
--- Then function supports set's error when failing.
--- 
--- @return string
function Jila_GetError() end

--- Get module, if not found returns nil.
--- 
--- @param name string Module name.
--- @return Module?
function Jila_GetModule(name) end

--- Global variables for storing some data across modules.
--- Careful! This not work in separate thread's. On separate
--- thread please use SharedScope_XXX functions.
--- 
--- Implementation details on SharedScope:
--- Read the value of XXXProperty from all threads is safe, but not write.
---
--- @type table
Scope = {}
