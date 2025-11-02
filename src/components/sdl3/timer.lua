---@meta timer

---@class SDL_DateTime
---@field second integer
---@field minute integer
---@field hour integer
---@field day integer
---@field day_of_week integer
---@field month integer
---@field year integer
SDL_DateTime = {}

---@param time integer
---@param localTime boolean
---
---@return SDL_DateTime SDL_DateTime year is 0 if failing.
---
--- 
--- @see SDL_GetError for read error.
function SDL_TimeToDateTime(time, localTime) end

---@param dateTime SDL_DateTime
---
---@return integer integer or 0 when error.
---
--- @see SDL_GetError for read error.
function SDL_DateTimeToTime(dateTime) end

---@return integer integer or 0 when error.
---
--- @see SDL_GetError for read error.
function SDL_GetCurrentTime() end
