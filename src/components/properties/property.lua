---@meta Property
---

--- @class IntProperty
--- @field value integer
IntProperty = {}

--- @param value integer
--- @return IntProperty
function Create_Int_Property(value) end

--- @class FloatProperty
--- @field value number
FloatProperty = {}

--- @param value number
--- @return FloatProperty
function Create_Float_Property(value) end

--- @class BoolProperty
--- @field value boolean
BoolProperty = {}

--- @param value boolean
--- @return BoolProperty
function Create_Bool_Property(value) end

--- @class CharProperty
--- @field str string
--- @field value string
CharProperty = {}

--- @return CharProperty
--- 
--- @overload fun(value: string): CharProperty
function Create_Char_Property() end
