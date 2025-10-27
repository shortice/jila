---@meta c_utils

---@overload fun(xOffset: integer)
function SameLine() end

--- Please use this when calling Render function.
---
---
--- @param text string
--- @return ImVec2
function CalcTextSize(text) end

---@overload fun(label: string)
function Separator() end

function ShowDemoWindow() end

function ShowMetricsWindow() end
