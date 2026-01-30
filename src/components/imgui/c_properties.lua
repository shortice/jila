---@meta c_properties

function ImSetNextItemAllowOverlap() end

--- @param col integer
--- @param vec ImVec4
function ImPushStyleColor(col, vec) end

function ImPopStyleColor() end

---@param idx integer
---@param val number
---
---@overload fun(idx: integer, val: ImVec2)
function ImPushStyleVar(idx, val) end

function ImPopStyleVar(count) end

---@param pos number number From 0.0 to 1.0
function ImSetScrollX(pos) end

---@param pos number number From 0.0 to 1.0
function ImSetScrollY(pos) end

---@param width integer
function ImPushItemWidth(width) end

function ImPopItemWidth() end

--- @param pos ImVec2
function ImSetCursorPos(pos) end

---@return ImVec2
function ImGetMousePos() end

---@return ImVec2
function ImGetContentRegionAvail() end

---@param size ImVec2
---
---@overload fun(x: integer, y: integer)
function ImSetNextWindowSize(size) end

---@param x integer
---@param y integer
---
---@overload fun(size: ImVec2)
function ImSetNextWindowPos(x, y) end

---@param x number
---@param y number
---
---@overload fun(pos: ImVec2)
function ImSetWindowPos(x, y) end

---@param x number
---@param y number
---
---@overload fun(size: ImVec2)
function ImSetWindowSize(x, y) end

---@param collapsed boolean
---
---@overload fun(collapsed: BoolProperty)
function ImSetWindowCollapsed(collapsed) end

---@return ImVec2
function ImGetWindowSize() end

---@return ImVec2
function ImGetWindowPos() end
