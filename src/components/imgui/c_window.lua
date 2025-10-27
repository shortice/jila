---@meta c_window

---@param name string
---@return boolean
---
---@overload fun(name: string, opened: BoolProperty): boolean
---@overload fun(name: string, opened: BoolProperty, flags: integer): boolean
---@overload fun(name: string, flags: integer)
function Begin(name) end

function End() end

---@param id string
---@return boolean
---
---@overload fun(id: string, size: ImVec2): boolean
---@overload fun(id: string, size: ImVec2, child_flags: integer): boolean
---@overload fun(id: string, size: ImVec2, child_flags: integer, window_flags: integer): boolean
function BeginChild(id) end

function EndChild() end
