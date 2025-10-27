---@meta c_input

---@param label string
---@param property IntProperty
---@param v_min integer
---@param v_max integer
---@return boolean
---
---@overload fun(label: string, property: IntProperty, v_min: integer, v_max: integer, format: string): boolean
---@overload fun(label: string, property: IntProperty, v_min: integer, v_max: integer, format: string, flags: integer): boolean
function SliderInt(label, property, v_min, v_max) end

---
---@param label string
---@param property CharProperty
---
---@return boolean
---
---@overload fun(label: string, property: CharProperty, flags: integer): boolean
function InputText(label, property) end

---
---@param label string
---@param property CharProperty
---
---@return boolean
---
---@overload fun(label: string, property: CharProperty, size: ImVec2): boolean
---@overload fun(label: string, property: CharProperty, size: ImVec2, flags: integer): boolean
function InputTextMultiline(label, property) end

---@param label string
---@param property IntProperty
---
---@return boolean
---
---@overload fun(label: string, property: IntProperty, step: integer): boolean
---@overload fun(label: string, property: IntProperty, step: integer, step_fast: integer): boolean
function InputInt(label, property) end

---@param label string
---@param property FloatProperty
---@param v_min number
---@param v_max number
---
---@return boolean
---
---@overload fun(label: string, property: FloatProperty, v_min: number, v_max: number, format: string): boolean
---@overload fun(label: string, property: FloatProperty, v_min: number, v_max: number, format: string, flags: integer): boolean
function SliderFloat(label, property, v_min, v_max) end

---@param label string
---@param property FloatProperty
---
---@return boolean
---
---@overload fun(label: string, property: FloatProperty, speed: number): boolean
---@overload fun(label: string, property: FloatProperty, speed: number, v_min: number, v_max: number): boolean
function DragFloat(label, property) end

---@param label string
---@param color ImVec4
---
---@return boolean
---
---@overload fun(label: string, color: ImVec4, flags: integer): boolean
function ColorEdit3(label, color) end

---@param label string
---@param color ImVec4
---
---@return boolean
---
---@overload fun(label: string, color: ImVec4, flags: integer): boolean
function ColorEdit4(label, color) end
