--- @type Module
local M = {
    name = "main",
    version = 0.1
}


function ThreadedResponse()
    local responseReq = SharedScope_GetC("Response")
    responseReq.str = ""
    local dataReq = SharedScope_GetC("Data")
    local completedReq = SharedScope_GetB("completedReq")

    Jila_Post(
        "http://www.httpbin.org/post",
        ---@diagnostic disable-next-line: param-type-mismatch
        responseReq,
        ---@diagnostic disable-next-line: need-check-nil
        dataReq.str
    )

    ---@diagnostic disable-next-line: need-check-nil
    local res_json = json.decode(responseReq.str)

    ---@diagnostic disable-next-line: need-check-nil
    responseReq.str = responseReq.str .. "\nJSON: " .. json.encode(res_json["data"])

    dataReq.str = ""
    completedReq.value = true
end

function M.Begin()

end

function M.End()

end

function M.BeginMainLoop()
    Scope.WindowSize = Jila_GetWindowSize()
    Scope.ParamsCount = 0

    ---@type table<number, [CharProperty, CharProperty]>
    Scope.Params = {}

    Scope.DataReq = SharedScope_CreateC("Data", "")
    Scope.Response = SharedScope_CreateC("Response", "")
    Scope.CompletedReq = SharedScope_CreateB("completedReq", true)
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

    if Scope.CompletedReq.value == true then
        if ImButton("POST", Create_ImVec2(Scope.WindowSize.x - 10, 25)) then
            Scope.DataReq.str = json.encode(GetParamsAsTable())
            Scope.CompletedReq.value = false
            Jila_Go(ThreadedResponse, "request")
        end
    end

    ImSeparator("Response: ")
    ImTextWrapped(Scope.Response.str)

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
