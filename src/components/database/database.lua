---@meta database

---@class DB
DB = {}

---@param name string
---
---@return DB
function Data_Create(name) end

---@param db DB
---@param key string
---
---@return string
function Data_Get(db, key) end

---@param db DB
---@param key string
---@param value string
---
---@return boolean
function Data_Set(db, key, value) end

---@param db DB
---@param key string
---
---@return boolean
function Data_Delete(db, key) end

---@param db DB
---@param key string
---
---@return boolean
function Data_IsExists(db, key) end
