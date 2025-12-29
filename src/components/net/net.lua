---@meta net

---@class Response
---@field status_code integer HTTP status code [readonly]
---@field text string Raw response text [readonly]
---@field raw_header string Raw response http header [readonly]
Response = {}

---If header not found then return "".
---
---@param res Response
---@param key string
---
---@return string
function Response_GetHeaderValue(res, key) end

---@param url string
---
---@return Response
function Get(url) end

---@param url string
---@param params table<string, string>
---
---@return Response
function Post(url, params) end
