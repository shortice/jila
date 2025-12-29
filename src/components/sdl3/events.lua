---@meta events

--- @enum SDL_EventType
SDL_EventType = {
    SDL_EVENT_WINDOW_RESIZED = 0,
    SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED = 0,
    SDL_EVENT_USER = 0
}

---
--- @class SDL_Event
--- @field type number SDL_Event type [readonly]
--- @field window SDL_WindowEvent [readonly]
--- @field user SDL_UserEvent [readonly]
SDL_Event = {}

--- @class SDL_WindowEvent
--- @field type number [readonly]
--- @field timestamp number [readonly]
--- @field windowID number [readonly]
--- @field data1 number [readonly]
--- @field data2 number [readonly]
SDL_WindowEvent = {}

--- @class SDL_UserEvent
--- @field type number [readonly]
--- @field code number [readonly]
--- @field timestamp number [readonly]
SDL_UserEvent = {}

