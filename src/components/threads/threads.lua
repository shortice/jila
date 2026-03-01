---@meta threads

--- Run the func on separate thread.
--- 
--- Careful! This function run on separate Lua VM. 
--- On this VM you can use only functions/modules in 'See'.
--- 
--- @see Jila_Sleep
--- @see Jila_Post
--- @see Jila_Get
--- @see Jila_Response_GetHeaderValue
--- @see json
---
--- @param func fun(): any
--- @param name string
function Jila_Go(func, name) end

--- @param ms number
function Jila_Sleep(ms) end

---
--- Shared storage functions.
--- Implementation details:
--- Read the value of XXXProperty from all threads is safe, but not write.
---

--- @param key string
--- 
--- @return FloatProperty|nil
function SharedScope_GetF(key) end

--- @param key string
--- @param value number
--- 
--- @return FloatProperty
function SharedScope_CreateF(key, value) end

--- @param key string
--- 
--- @return IntProperty|nil
function SharedScope_GetI(key) end

--- @param key string
--- @param value number
--- 
--- @return IntProperty
function SharedScope_CreateI(key, value) end

--- @param key string
--- 
--- @return CharProperty|nil
function SharedScope_GetC(key) end

--- @param key string
--- @param value string
--- 
--- @return CharProperty
function SharedScope_CreateC(key, value) end

--- @param key string
--- 
--- @return BoolProperty|nil
function SharedScope_GetB(key) end

--- @param key string
--- @param value boolean
--- 
--- @return BoolProperty
function SharedScope_CreateB(key, value) end

--- @param key string
--- 
--- @return boolean
function SharedScope_Delete(key) end
