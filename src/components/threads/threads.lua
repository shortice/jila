---@meta threads

--- @enum ThreadStatusCode
StatusCode = {
    COMPLETED = 2,
    ERROR = 3,
    RUNNING = 1,
    STARTING = 0
}

--- @class ThreadMessage
--- @field threadName string
--- @field statusCode ThreadStatusCode
--- @field var number|string|nil
ThreadMessage = {}

--- Run the func on separate thread.
--- 
--- Careful! This function run on separate Lua VM. 
--- On this VM you can use only functions in 'See'.
--- This is temporary.
--- 
--- @see PushThreadMessage
--- @see SDL_Delay
---
--- @param func fun(): any
--- @param name string
function Go(func, name) end

--- Extract event from separate thread.
--- 
--- SDL_UserEvent code: 1002.
--- 
--- You always need calling this function when you using
--- thread system. Because we allocate some memory when
--- pushing events to main thread from separated thread.
--- @param event SDL_UserEvent
--- @return ThreadMessage
function GetThreadMessage(event) end

---Push event to main thread.
--- 
---@param threadName string
---@param message number|string|nil
function PushThreadMessage(threadName, message) end

--- This function can call on main thread.
--- @param time number
function SDL_Delay(time) end
