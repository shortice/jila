---@meta logger

---
---@class Jila_Logger
---@field name string Jila_Logger name
Jila_Logger = {}

--- The Jila_Logger constructor
---@param name string Jila_Logger name
---@return Jila_Logger
function Create_Logger(name) end

---@param message string Message
function Jila_Logger:Warn(message) end

---@param message string Message
function Jila_Logger:Error(message) end

---@param message string Message
function Jila_Logger:Debug(message) end

---@param message string Message
function Jila_Logger:Info(message) end
