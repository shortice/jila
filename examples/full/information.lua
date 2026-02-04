---
--- @type Module
local M = {
    name = "information",
    version = 0.1
}

function M.Begin()
    Scope.CurrentCwd = ""

    ---@type Jila_FsState
    Scope.FsState = nil

    Scope.FsRecursive = Create_Bool_Property(false)
end

function M.End() end

function M.Render(time)
    ImText("Current platform: " .. jila_platform)
    ImTextWrapped("Base path: " .. Jila_Fs_GetBasePath())
    ImTextWrapped(
        'Pref path ("Shortice" org and "Jila demo" as name): ' .. Jila_Fs_GetPrefPath(
            "Shortice", "Jila demo"
        )
    )

    if ImButton("Select folder") then
        Jila_OpenFolderDialog()
    end

    ImCheckbox("Recursive?", Scope.FsRecursive)
    ImTextWrapped("Current folder: " .. Scope.CurrentCwd)
    ImSeparator("Filesystem: ")

    if Scope.FsState == nil then
        return
    end

    if ImBeginTable("FileSystem Table", 3) then
        ImTableSetupColumn("Path")
        ImTableSetupColumn("Name")
        ImTableSetupColumn("Ext")
        ImTableHeadersRow()

        for k, v in ipairs(Scope.FsState.currentEntries) do
            ImTableNextRow()
            ImTableNextColumn()
            ImTextWrapped(v.path)
            ImTableNextColumn()
            ImTextWrapped(v.name)
            ImTableNextColumn()
            ImTextWrapped(v.ext)
        end
        ImEndTable()
    end
end

--- TODO: fix random crash in this example (memory issue?)
function M.Event(event)
    if (event.type == Jila_EventType.Jila_EVENT_USER) then
        if (event.user.code ~= 1005) then return end

        local dialog = Jila_GetDialogState(event.user)

        if dialog.is_folder == false then return end

        if dialog.selected_folder == "" then return end

        Scope.CurrentCwd = dialog.selected_folder

        if Scope.FsState == nil then
            Scope.FsState = Jila_Create_FS_State(Scope.CurrentCwd)
        else
            Scope.FsState.currentCwd = Scope.CurrentCwd
        end

        Jila_Fs_GetAllFiles(Scope.FsState, Scope.FsRecursive.value)
    end
end

return M -- Required!!!

