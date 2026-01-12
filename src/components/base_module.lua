--- @meta base_modules

--- @class Module
--- 
--- @field name string Module name
--- @field version number Module version
--- @field scope table? Module variable container
--- 
--- Module type (but actual real type is standart lua table)
Module = {}

--- Called when module initialization.
---
--- Can accessed on all modules.
function Module.Begin() end

--- Called when module deinitialization.
---
--- Can accessed on all modules.
function Module.End() end

--- Called when application is starting.
---
--- Can accessed only on "main" module..
function Module.BeginMainLoop() end

--- Called each frame for rendering some things.
---
--- Can accessed only on "main" module..
--- 
--- @param time integer Represents milliseconds count elapsed since initialize SDL.
function Module.Render(time) end

--- Called when process each event from the Application Window.
--- 
--- Can accessed only on "main" module.
--- 
--- @param event SDL_Event
function Module.Event(event) end
