---@meta filesystem

---@class Jila_FsEntry
---@field path string Entry path [readonly]
---@field name string Entry name [readonly]
---@field ext string Entry extension [readonly]
---@field isDir boolean Is this entry is directory? [readonly]
Jila_FsEntry = {}

---@class Jila_FsState
---@field currentEntries Jila_FsEntry[] Current entries [readonly]
---@field currentCwd string Current cwd
---@field includeHidden boolean Include hidden entries?
Jila_FsState = {}

---@param currentCwd string
---
---@return Jila_FsState
function Create_FS_State(currentCwd) end

--- @param state Jila_FsState
function Jila_Fs_GetFolders(state) end

--- @param state Jila_FsState
--- @param recursive boolean
--- @overload fun(state: Jila_FsState, recursive: boolean, exts: string[])
function Jila_Fs_GetAllFiles(state, recursive) end

---@return string
function Jila_Fs_GetHomePath() end
