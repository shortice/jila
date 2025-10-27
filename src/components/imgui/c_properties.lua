---@meta c_properties

function SetNextItemAllowOverlap() end

--- @param col integer
--- @param vec ImVec4
function PushStyleColor(col, vec) end

function PopStyleColor() end

---@param idx integer
---@param val number
---
---@overload fun(idx: integer, val: ImVec2)
function PushStyleVar(idx, val) end

function PopStyleVar(count) end

---@param pos number number From 0.0 to 1.0
function SetScrollX(pos) end

---@param pos number number From 0.0 to 1.0
function SetScrollY(pos) end

---@param width integer
function PushItemWidth(width) end

function PopItemWidth() end

--- @param pos ImVec2
function SetCursorPos(pos) end

---@return ImVec2
function GetMousePos() end

---@return ImVec2
function GetContentRegionAvail() end

---@param size ImVec2
---
---@overload fun(x: integer, y: integer)
function SetNextWindowSize(size) end

---@param x integer
---@param y integer
---
---@overload fun(size: ImVec2)
function SetNextWindowPos(x, y) end

---@param x number
---@param y number
---
---@overload fun(pos: ImVec2)
function SetWindowPos(x, y) end

---@param x number
---@param y number
---
---@overload fun(size: ImVec2)
function SetWindowSize(x, y) end

---@param collapsed boolean
---
---@overload fun(collapsed: BoolProperty)
function SetWindowCollapsed(collapsed) end

---@return ImVec2
function GetWindowSize() end

---@return ImVec2
function GetWindowPos() end
