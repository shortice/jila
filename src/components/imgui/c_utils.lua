---@meta c_utils

---@overload fun(xOffset: integer)
function ImSameLine() end

--- Please use this when calling Render function.
---
---
--- @param text string
--- @return ImVec2
function ImCalcTextSize(text) end

---@overload fun(label: string)
function ImSeparator() end

function ImShowDemoWindow() end

function ImShowMetricsWindow() end

function ImScrollWhenDragging() end
