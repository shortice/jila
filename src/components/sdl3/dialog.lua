---@meta dialog

---@class Jila_DialogState
---
---@field is_folder boolean
---@field selected_files string[]
---@field selected_folder string
---
Jila_DialogState = {}

--- Show open file dialog.
---
---@overload fun(allow_extensions: string[])
---
--- When user select file/folder then created new SDL event with 1005 code.
function Jila_OpenFileDialog() end

--- Show open folder dialog.
---
--- When user select file/folder then created new SDL event with 1005 code.
function Jila_OpenFolderDialog() end

---@param event Jila_UserEvent
---
---Code: 1005 user event
---
---@return Jila_DialogState
function Jila_GetDialogState(event) end
