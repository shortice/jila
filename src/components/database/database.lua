---@meta database

---@class DB
---
---@field objects [string, string][] Key-value array
DB = {}

---@param path string
---
---Create (or load) sqlite3 database.
---When you deleting the DB object, connection automatically closes.
---
---@return DB? DB or nil when error
---
---@see SDL_GetError for read error.
---@nodiscard
function Data_Connect(path) end

---@param db DB
---@param query string
---
---Execute the SQL query (or query's).
---This is unsafe function, because can processed SQL-Injections. 
---Always validate user's input.
---
---@return boolean boolean false when error.
---
---@see SDL_GetError for read error.
function Data_Exec(db, query) end
