---@meta timer

---@class Jila_DateTime
---@field second integer
---@field minute integer
---@field hour integer
---@field day integer
---@field day_of_week integer
---@field month integer
---@field year integer
Jila_DateTime = {}

---@param time integer
---@param localTime boolean
---
---@return Jila_DateTime SDL_DateTime year is 0 if failing.
---
--- 
--- @see Jila_GetError for read error.
function Jila_TimeToDateTime(time, localTime) end

---@param dateTime Jila_DateTime
---
---@return integer integer or 0 when error.
---
--- @see Jila_GetError for read error.
function Jila_DateTimeToTime(dateTime) end

---@return integer integer or 0 when error.
---
--- @see Jila_GetError for read error.
function Jila_GetCurrentTime() end


---@param localTime boolean
---@return Jila_DateTime SDL_DateTime year is 0 if failing.
---
--- @see Jila_GetError for read error.
function Jila_GetCurrentDateTime(localTime) end
