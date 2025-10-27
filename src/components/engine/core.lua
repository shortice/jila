---@meta core

--- Получает ошибку или "", если нифига нету.
---
--- @return string
function SDL_GetError() end

--- Получает загруженный модуль по имени.
---@param name string Имя модуля.
---@return table Возвращает таблицу (sol::table) представляющую модуль или nil.
function GetModule(name) end

---Глобальная переменная для хранения разных значений.
---Обратите внимание, она не работает только в основном (main) потоке.
---
---@type table
Scope = {}
