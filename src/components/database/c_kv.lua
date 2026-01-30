---@meta c_kv

---@class Jila_KvDB
---
Jila_KvDB = {}

---@param path string
---
---Create (or load) sqlite3 database.
---When you deleting the Jila_KvDB object, connection automatically closes.
---
---@return Jila_KvDB? Jila_KvDB or nil when error
---
--- @see Jila_GetError for read error.
---@nodiscard
function Jila_Kv_Connect(path) end

---@param db Jila_KvDB
---@param key string
---@param value string
---
---Set's a value.
---
---This is safe function and not can SQL-injected.
---
---@return boolean boolean false when error.
---
--- @see Jila_GetError for read error.
function Jila_Kv_Set(db, key, value) end

---@param db Jila_KvDB
---@param key string
---
---Get value from specific key.
---
---This is safe function and not can SQL-injected.
---
---@return string string or emptry.
---
--- @see Jila_GetError for read error.
function Jila_Kv_Get(db, key) end

---@param db Jila_KvDB
---@param key string
---
---Delete key.
---
---This is safe function and not can SQL-injected.
---
function Jila_Kv_Delete(db, key) end

---@param db Jila_KvDB
---@param key string
---
---This is safe function and not can SQL-injected.
---
---@return boolean
function Jila_Kv_IsExist(db, key) end
