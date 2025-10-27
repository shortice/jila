---@meta filesystem

---@class FsEntry
---@field path string
---@field name string
---@field ext string
---@field isDir boolean
FsEntry = {}

---@class FsState
---@field currentEntries FsEntry[]
---@field currentCwd string
---@field includeHidden boolean
FsState = {}

---@param currentCwd string
---
---@return FsState
function FsState.new(currentCwd) end

--- @param state FsState
function Fs_GetFolders(state) end

--- @param state FsState
--- @param recursive boolean
--- @overload fun(state: FsState, recursive: boolean, exts: string[])
function Fs_GetAllFiles(state, recursive) end

---@return string
function Fs_GetHomePath() end
