---@meta android

---Careful! 
---Actual result of this function not returning value.
---I use custom SDL_Event for this, because this function
---use another thread.
---
---Handle it on Event func.
---
---Codes:
---1003 - user accept request;
---1004 - user dont accept request.
---
---@param permission string
---
---@return boolean boolearn
function android_RequestPermission(permission) end
