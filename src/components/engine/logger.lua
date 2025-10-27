---@meta logger

---
---@class Logger
Logger = {}

--- Конструктор объекта Logger.
---@param name string Имя логгера.
---@return Logger Новый экземпляр Logger.
function Logger.new(name) end

---@type string Имя данного логгера.
Logger.name = nil

--- Записывает предупреждающее сообщение.
---@param message string Сообщение для логирования.
function Logger:Warn(message) end

--- Записывает сообщение об ошибке.
---@param message string Сообщение для логирования.
function Logger:Error(message) end

--- Записывает отладочное сообщение.
---@param message string Сообщение для логирования.
function Logger:Debug(message) end

--- Записывает информационное сообщение.
---@param message string Сообщение для логирования.
function Logger:Info(message) end
