---@meta net

---@class Response
---@field status_code integer
---@field text string
---@field raw_header string
Response = {}

---If header not found then return "".
---
---@param key string
---
---@return string
function Response:getHeaderValue(key) end

---@param url string
---
---@return Response
function Get(url) end

---@param url string
---@param params table<string, string>
---
---@return Response
function Post(url, params) end
