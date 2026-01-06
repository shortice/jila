---@meta c_input

---@param label string
---@param Property IntProperty
---@param v_min integer
---@param v_max integer
---@return boolean
---
---@overload fun(label: string, Property: IntProperty, v_min: integer, v_max: integer, format: string): boolean
---@overload fun(label: string, Property: IntProperty, v_min: integer, v_max: integer, format: string, flags: integer): boolean
function SliderInt(label, Property, v_min, v_max) end

---
---@param label string
---@param Property CharProperty
---
---@return boolean
---
---@overload fun(label: string, Property: CharProperty, flags: integer): boolean
function InputText(label, Property) end

---
---@param label string
---@param Property CharProperty
---
---@return boolean
---
---@overload fun(label: string, Property: CharProperty, size: ImVec2): boolean
---@overload fun(label: string, Property: CharProperty, size: ImVec2, flags: integer): boolean
function InputTextMultiline(label, Property) end

---@param label string
---@param Property IntProperty
---
---@return boolean
---
---@overload fun(label: string, Property: IntProperty, step: integer): boolean
---@overload fun(label: string, Property: IntProperty, step: integer, step_fast: integer): boolean
function InputInt(label, Property) end

---@param label string
---@param Property FloatProperty
---@param v_min number
---@param v_max number
---
---@return boolean
---
---@overload fun(label: string, Property: FloatProperty, v_min: number, v_max: number, format: string): boolean
---@overload fun(label: string, Property: FloatProperty, v_min: number, v_max: number, format: string, flags: integer): boolean
function SliderFloat(label, Property, v_min, v_max) end

---@param label string
---@param Property FloatProperty
---
---@return boolean
---
---@overload fun(label: string, Property: FloatProperty, speed: number): boolean
---@overload fun(label: string, Property: FloatProperty, speed: number, v_min: number, v_max: number): boolean
function DragFloat(label, Property) end

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
