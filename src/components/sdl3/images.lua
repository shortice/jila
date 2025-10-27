---@meta b_images

--- @class SDL_Texture
SDL_Texture = {}


---
---@see Image
---@see ImageButton
---@see SDL_GetTextureSize
---
--- @param path string Path of the picture.
--- @return SDL_Texture|nil Texture or nil when error.
function SDL_CreateImageTexture(path) end


--- @param texture SDL_Texture
--- @return ImVec2 ImVec2 or ImVec2(-1, -1) when error.
function SDL_GetTextureSize(texture) end

--- @param texture SDL_Texture
--- @param imageSize ImVec2
function Image(texture, imageSize) end

--- @param label string
--- @param texture SDL_Texture
--- @param imageSize ImVec2
function ImageButton(label, texture, imageSize) end
