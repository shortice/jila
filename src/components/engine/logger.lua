---@meta logger

---
---@class Logger
---@field name string Logger name
Logger = {}

--- The Logger constructor
---@param name string Logger name
---@return Logger
function Create_Logger(name) end

---@param message string Message
function Logger:Warn(message) end

---@param message string Message
function Logger:Error(message) end

---@param message string Message
function Logger:Debug(message) end

---@param message string Message
function Logger:Info(message) end
