---@meta micro


---@class Microphone
Microphone = {}

--- @return Microphone
function SDL_CreateMicro() end

--- @param micro Microphone
---
--- @return boolean
function SDL_MicroPause(micro) end

--- @param micro Microphone
---
--- @return boolean
function SDL_MicroResume(micro) end

--- @param micro Microphone
---
--- @return boolean
function SDL_MicroPaused(micro) end

--- @param micro Microphone
--- @param fileName string
---
--- @return boolean
function SDL_MicroSaveWAV(micro, fileName) end
