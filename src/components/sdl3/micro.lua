---@meta micro


---@class Jila_Microphone
Jila_Microphone = {}

--- @return Jila_Microphone? Microphone or nil when error.
--- 
--- @see Jila_GetError for read error.
function Jila_CreateMicro() end

--- @param micro Jila_Microphone
---
--- @return boolean boolean false when error.
--- 
--- @see Jila_GetError for read error.
function Jila_MicroPause(micro) end

--- @param micro Jila_Microphone
---
--- @return boolean boolean false when error.
--- 
--- @see Jila_GetError for read error.
function Jila_MicroResume(micro) end

--- @param micro Jila_Microphone
---
--- @return boolean
function Jila_MicroPaused(micro) end

--- @param micro Jila_Microphone
--- @param fileName string
---
--- @return boolean boolean always true.
function Jila_MicroSaveWAV(micro, fileName) end
