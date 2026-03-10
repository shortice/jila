---@meta net

---@class Jila_Response
---@field status_code integer HTTP status code [readonly]
---@field raw_header string Raw response http header [readonly]
Jila_Response = {}

---If header not found then returns nil.
---
---@param res Jila_Response
---@param key string
---
---@return string|nil
function Jila_Response_GetHeaderValue(res, key) end

---@param url string
---@param data CharProperty
---
---@return Jila_Response
function Jila_Get(url, data) end

---@param url string
---@param data CharProperty
---
---@return Jila_Response
---
---@overload fun(url: string, data: CharProperty, json: string): Jila_Response
function Jila_Post(url, data) end
