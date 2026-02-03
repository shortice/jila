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
    ImTextWrapped("Base path: " .. Jila_Fs_GetBasePath())
    ImTextWrapped(
        'Pref path ("Shortice" org and "Jila demo" as name): ' .. Jila_Fs_GetPrefPath(
            "Shortice", "Jila demo"
        )
    )
end

return M -- Required!!!

