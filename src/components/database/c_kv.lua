---@meta c_kv

---@class KvDB
---
KvDB = {}

---@param path string
---
---Create (or load) sqlite3 database.
---When you deleting the KvDB object, connection automatically closes.
---
---@return KvDB? KvDB or nil when error
---
---@see SDL_GetError for read error.
---@nodiscard
function Kv_Connect(path) end

---@param db KvDB
---@param key string
---@param value string
---
---Set's a value.
---
---This is safe function and not can SQL-injected.
---
---@return boolean boolean false when error.
---
---@see SDL_GetError for read error.
function Kv_Set(db, key, value) end

---@param db KvDB
---@param key string
---
---Get value from specific key.
---
---This is safe function and not can SQL-injected.
---
---@return string string or emptry.
---
---@see SDL_GetError for read error.
function Kv_Get(db, key) end

---@param db KvDB
---@param key string
---
---Delete key.
---
---This is safe function and not can SQL-injected.
---
function Kv_Delete(db, key) end

---@param db KvDB
---@param key string
---
---This is safe function and not can SQL-injected.
---
---@return boolean
function Kv_IsExist(db, key) end
