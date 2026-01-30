---@meta b_images

--- @class Jila_Texture
Jila_Texture = {}


---
---@see ImImage
---@see ImImageButton
---@see Jila_GetTextureSize
---
--- @param path string Path of the picture.
--- @return Jila_Texture? Texture or nil when error.
---
--- @see Jila_GetError for read error.
function Jila_CreateImageTexture(path) end

--- @param texture Jila_Texture
--- @return ImVec2 ImVec2 or ImVec2(-1, -1) when error.
---
--- @see Jila_GetError for read error.
function Jila_GetTextureSize(texture) end
