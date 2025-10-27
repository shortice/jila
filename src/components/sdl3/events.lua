---@meta events

--- @enum SDL_EventType
SDL_EventType = {
    SDL_EVENT_WINDOW_RESIZED = 0,
    SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED = 0,
    SDL_EVENT_USER = 0
}

---
--- @class SDL_Event
--- @field type number
--- @field window SDL_WindowEvent
--- @field user SDL_UserEvent
SDL_Event = {}

--- @class SDL_WindowEvent
--- @field type number
--- @field timestamp number
--- @field windowID number
--- @field data1 number
--- @field data2 number
SDL_WindowEvent = {}

--- @class SDL_UserEvent
--- @field type number
--- @field code number
--- @field timestamp number
SDL_UserEvent = {}

