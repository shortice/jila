---@meta c_item_state

---@return boolean
function ImIsItemHovered() end

---@param key_code integer
---@param repeat_ boolean
---
---@return boolean
---
---@overload fun(key_code: integer): boolean
function ImIsKeyPressed(key_code, repeat_) end

---@param mouse_button integer
---
---@return boolean
function ImIsMouseDown(mouse_button) end

---@return boolean
function ImIsDoubleClicked() end
