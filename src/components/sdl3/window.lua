---@meta window

---@param title string
---@return boolean boolean false when error.
---
--- @see Jila_GetError for read error.
function Jila_SetWindowTitle(title) end

---@return ImVec2 size w and h is 0 when error.
---
--- @see Jila_GetError for read error.
function Jila_GetWindowSize() end

---@return ImVec4 size w and h is 0 when error.
---
--- @see Jila_GetError for read error.
function Jila_GetWindowSafeArea() end

---@param size ImVec2
---
---@return boolean boolean false when error.
---
--- @see Jila_GetError for read error.
function Jila_SetWindowSize(size) end
