---@meta c_input

---@param label string
---@param Property IntProperty
---@param v_min integer
---@param v_max integer
---@return boolean
---
---@overload fun(label: string, Property: IntProperty, v_min: integer, v_max: integer, format: string): boolean
---@overload fun(label: string, Property: IntProperty, v_min: integer, v_max: integer, format: string, flags: integer): boolean
function ImSliderInt(label, Property, v_min, v_max) end

---
---@param label string
---@param Property CharProperty
---
---@return boolean
---
---@overload fun(label: string, Property: CharProperty, flags: integer): boolean
function ImInputText(label, Property) end

---
---@param label string
---@param Property CharProperty
---
---@return boolean
---
---@overload fun(label: string, Property: CharProperty, size: ImVec2): boolean
---@overload fun(label: string, Property: CharProperty, size: ImVec2, flags: integer): boolean
function ImInputTextMultiline(label, Property) end

---@param label string
---@param Property IntProperty
---
---@return boolean
---
---@overload fun(label: string, Property: IntProperty, step: integer): boolean
---@overload fun(label: string, Property: IntProperty, step: integer, step_fast: integer): boolean
function ImInputInt(label, Property) end

---@param label string
---@param Property FloatProperty
---@param v_min number
---@param v_max number
---
---@return boolean
---
---@overload fun(label: string, Property: FloatProperty, v_min: number, v_max: number, format: string): boolean
---@overload fun(label: string, Property: FloatProperty, v_min: number, v_max: number, format: string, flags: integer): boolean
function ImSliderFloat(label, Property, v_min, v_max) end

---@param label string
---@param Property FloatProperty
---
---@return boolean
---
---@overload fun(label: string, Property: FloatProperty, speed: number): boolean
---@overload fun(label: string, Property: FloatProperty, speed: number, v_min: number, v_max: number): boolean
function ImDragFloat(label, Property) end

---@param label string
---@param color ImVec4
---
---@return boolean
---
---@overload fun(label: string, color: ImVec4, flags: integer): boolean
function ImColorEdit3(label, color) end

---@param label string
---@param color ImVec4
---
---@return boolean
---
---@overload fun(label: string, color: ImVec4, flags: integer): boolean
function ImColorEdit4(label, color) end
