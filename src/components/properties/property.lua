
---@meta property
--- 

--- @class IntProperty
--- @field value integer
IntProperty = {}

--- @param value integer
--- @return IntProperty
function IntProperty.new(value) end


--- @class FloatProperty
--- @field value number
FloatProperty = {}

--- @param value number
--- @return FloatProperty
function FloatProperty.new(value) end


--- @class BoolProperty
--- @field value boolean
BoolProperty = {}

--- @param value boolean
--- @return BoolProperty
function BoolProperty.new(value) end

--- @class CharProperty
--- @field str string
CharProperty = {}

--- @return CharProperty
--- @overload fun(string): CharProperty
--- @overload fun(integer): CharProperty
function CharProperty.new() end
