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
---This functional not working on Android at this moment.
---
---@return Jila_FsState
function Create_FS_State(currentCwd) end

--- @param state Jila_FsState
function Jila_Fs_GetFolders(state) end

--- @param state Jila_FsState
--- @param recursive boolean
--- @overload fun(state: Jila_FsState, recursive: boolean, exts: string[])
function Jila_Fs_GetAllFiles(state, recursive) end


--- A function for getting a internal path of the Application.
---
--- This is safe place for writing/reading files. 
--- The returned path is guaranteed to end with a path separator 
--- ('\' on Windows, '/' on most other platforms).
---
--- @param org string Organization/author name
--- @param name string Name of this application
--- 
--- @return string
function Jila_Fs_GetPrefPath(org, name) end


--- A function for getting a path to the application data directory.
---
--- On android please do not use this function for getting assets files path, instead
--- just use path like this "test.png" for opening file "test.png" in the assets
--- directory inside .apk.
---
--- @return string
function Jila_Fs_GetBasePath() end
