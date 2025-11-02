---@meta micro


---@class Microphone
Microphone = {}

--- @return Microphone? Microphone or nil when error.
--- 
--- @see SDL_GetError for read error.
function SDL_CreateMicro() end

--- @param micro Microphone
---
--- @return boolean boolean false when error.
--- 
--- @see SDL_GetError for read error.
function SDL_MicroPause(micro) end

--- @param micro Microphone
---
--- @return boolean boolean false when error.
--- 
--- @see SDL_GetError for read error.
function SDL_MicroResume(micro) end

--- @param micro Microphone
---
--- @return boolean
function SDL_MicroPaused(micro) end

--- @param micro Microphone
--- @param fileName string
---
--- @return boolean boolean always true.
function SDL_MicroSaveWAV(micro, fileName) end
