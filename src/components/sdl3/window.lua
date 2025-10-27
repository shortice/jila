---@meta window

---@param title string
---@return boolean boolean
function SDL_SetWindowTitle(title) end

---@return ImVec2 size
---
function SDL_GetWindowSize() end

---@return ImVec4 size
---
function SDL_GetWindowSafeArea() end

---@param size ImVec2
---
---@return boolean boolean
function SDL_SetWindowSize(size) end
