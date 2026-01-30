--- @type Module
local M = {
    name = "main",
    version = 0.1
}

function M.Begin()

end

function M.End()

end

function M.BeginMainLoop()
    Scope.WindowSize = Jila_GetWindowSize()
    Scope.ParamsCount = 0

    ---@type table<number, [CharProperty, CharProperty]>
    Scope.Params = {}
    Scope.Response = "None"
end

---@param number number
function RenderOneParam(number)
    ImTableNextColumn()
    ImInputText("##param-" .. number .. "key", Scope.Params[number][1])
    ImTableNextColumn()
    ImInputText("##param-" .. number .. "value", Scope.Params[number][2])
    ImTableNextColumn()

    if ImButton(ICON_FA_X .. "##param-" .. number) then
        table.remove(Scope.Params, number)
        Scope.ParamsCount = Scope.ParamsCount - 1
    end
end

function RenderParams()
    local i = 0

    while i < Scope.ParamsCount do
        RenderOneParam(i + 1)
        i = i + 1
    end
end

---@return table
function GetParamsAsTable()
    local tbl = {}

    for k, v in pairs(Scope.Params) do
        tbl[v[1].str] = v[2].str
    end

    return tbl
end

---@param time number
function M.Render(time)
    ImSetNextWindowPos(Create_ImVec2())
    ImSetNextWindowSize(Scope.WindowSize)
    ImBegin("HTTP API")

    ImText("Params count: " .. tostring(Scope.ParamsCount))

    if ImBeginTable("Params", 3) then
        ImTableSetupColumn("Key")
        ImTableSetupColumn("Value")
        ImTableSetupColumn("Delete?")
        ImTableHeadersRow()

        RenderParams()

        ImEndTable()
    end

    if ImButton("ADD PARAM", Create_ImVec2(Scope.WindowSize.x - 10, 25)) then
        Scope.ParamsCount = Scope.ParamsCount + 1

        Scope.Params[Scope.ParamsCount] = {
            Create_Char_Property(), -- key
            Create_Char_Property()  -- value
        }
    end

    if ImButton("POST", Create_ImVec2(Scope.WindowSize.x - 10, 25)) then
        local res = Jila_Post(
            "http://www.httpbin.org/post",
            json.encode(GetParamsAsTable())
        )
        local res_json = json.decode(res.text)
        Scope.Response = res.text .. "\nJSON: " .. json.encode(res_json["data"])
    end

    ImSeparator("Response: ")
    ImTextWrapped(Scope.Response)

    ImEnd()
end

---@param event Jila_Event
function M.Event(event)
    if event.type == Jila_EventType.Jila_EVENT_WINDOW_PIXEL_SIZE_CHANGED then
        Scope.WindowSize.x = event.window.data1
        Scope.WindowSize.y = event.window.data2
    end
end

return M -- Required!!!
