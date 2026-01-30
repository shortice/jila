---@meta events

--- @enum Jila_EventType
Jila_EventType = {
    Jila_EVENT_WINDOW_RESIZED = 0,
    Jila_EVENT_WINDOW_PIXEL_SIZE_CHANGED = 0,
    Jila_EVENT_USER = 0
}

---
--- @class Jila_Event
--- @field type number Jila_Event type [readonly]
--- @field window Jila_WindowEvent [readonly]
--- @field user Jila_UserEvent [readonly]
Jila_Event = {}

--- @class Jila_WindowEvent
--- @field type number [readonly]
--- @field timestamp number [readonly]
--- @field windowID number [readonly]
--- @field data1 number [readonly]
--- @field data2 number [readonly]
Jila_WindowEvent = {}

--- @class Jila_UserEvent
--- @field type number [readonly]
--- @field code number [readonly]
--- @field timestamp number [readonly]
Jila_UserEvent = {}

