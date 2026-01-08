---@meta net

---@class Response
---@field status_code integer HTTP status code [readonly]
---@field text string Raw response text [readonly]
---@field raw_header string Raw response http header [readonly]
Response = {}

---If header not found then returns nil.
---
---@param res Response
---@param key string
---
---@return string|nil
function Response_GetHeaderValue(res, key) end

---@param url string
---
---@return Response
function Get(url) end

---@param url string
---
---@return Response
---
---@overload fun(url: string, json: string): Response
function Post(url) end
