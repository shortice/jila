---
--- @type Module
local M = {
    name = "information",
    version = 0.1
}

function M.Begin() end

function M.End() end

function M.Render(time)
    ImText("Current platform: " .. jila_platform)
end

return M -- Required!!!

