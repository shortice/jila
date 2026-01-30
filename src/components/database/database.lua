---@meta database

---@class Jila_DB
---
---@field objects [string, string][] Key-value array [readonly]
Jila_DB = {}

---@param path string
---
---Create (or load) sqlite3 database.
---When you deleting the DB object, connection automatically closes.
---
---@return Jila_DB? DB or nil when error
---
--- @see Jila_GetError for read error.
---@nodiscard
function Jila_Data_Connect(path) end

---@param db Jila_DB
---@param query string
---
---Execute the SQL query (or query's).
---This is unsafe function, because can processed SQL-Injections. 
---Always validate user's input.
---
---@return boolean boolean false when error.
---
--- @see Jila_GetError for read error.
function Jila_Data_Exec(db, query) end
