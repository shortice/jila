---@meta c_item_state

---@return boolean
function IsItemHovered() end

---@param key_code integer
---@param repeat_ boolean
---
---@return boolean
---
---@overload fun(key_code: integer): boolean
function IsKeyPressed(key_code, repeat_) end

---@param mouse_button integer
---
---@return boolean
function IsMouseDown(mouse_button) end

---@return boolean
function IsDoubleClicked() end
