---@meta window

---@param title string
---@return boolean boolean false when error.
---
--- @see SDL_GetError for read error.
function SDL_SetWindowTitle(title) end

---@return ImVec2 size w and h is 0 when error.
---
--- @see SDL_GetError for read error.
function SDL_GetWindowSize() end

---@return ImVec4 size w and h is 0 when error.
---
--- @see SDL_GetError for read error.
function SDL_GetWindowSafeArea() end

---@param size ImVec2
---
---@return boolean boolean false when error.
---
--- @see SDL_GetError for read error.
function SDL_SetWindowSize(size) end
