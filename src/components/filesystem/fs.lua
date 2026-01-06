---@meta filesystem

---@class FsEntry
---@field path string Entry path [readonly]
---@field name string Entry name [readonly]
---@field ext string Entry extension [readonly]
---@field isDir boolean Is this entry is directory? [readonly]
FsEntry = {}

---@class FsState
---@field currentEntries FsEntry[] Current entries [readonly]
---@field currentCwd string Current cwd
---@field includeHidden boolean Include hidden entries?
FsState = {}

---@param currentCwd string
---
---@return FsState
function Create_FS_State(currentCwd) end

--- @param state FsState
function Fs_GetFolders(state) end

--- @param state FsState
--- @param recursive boolean
--- @overload fun(state: FsState, recursive: boolean, exts: string[])
function Fs_GetAllFiles(state, recursive) end

---@return string
function Fs_GetHomePath() end
