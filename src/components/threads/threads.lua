---@meta threads

--- @enum Jila_ThreadStatusCode
Jila_ThreadStatusCode = {
    COMPLETED = 2,
    ERROR = 3,
    RUNNING = 1,
    STARTING = 0
}

--- @class Jila_ThreadMessage
--- @field threadName string
--- @field statusCode Jila_ThreadStatusCode
--- @field var number|string|nil
Jila_ThreadMessage = {}

--- Run the func on separate thread.
--- 
--- Careful! This function run on separate Lua VM. 
--- On this VM you can use only functions/modules in 'See'.
--- 
--- @see Jila_PushThreadMessage
--- @see Jila_Sleep
--- @see Jila_Post
--- @see Jila_Get
--- @see Jila_Response_GetHeaderValue
--- @see json
---
--- @param func fun(): any
--- @param name string
function Jila_Go(func, name) end

--- Extract event from separate thread.
--- 
--- SDL_UserEvent code: 1002.
--- @param event Jila_UserEvent
--- @return Jila_ThreadMessage
function Jila_GetThreadMessage(event) end

---Push event to main thread.
--- 
---@param threadName string
---@param message number|string|nil
function Jila_PushThreadMessage(threadName, message) end

--- This function can call on main thread.
--- @param time number
function Jila_Sleep(time) end
