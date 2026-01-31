---
--- @type Module
local M = {
    name = "database",
    version = 0.1
}

function M.Begin()
    Scope.KvData = Jila_Kv_Connect("kv.db")

    Scope.KvKey = Create_Char_Property()
    Scope.KvValue = Create_Char_Property()
end

function M.End() end

function M.Render(time)
    ImText("Key: "); ImSameLine()
    ImInputText("##key_kv_input", Scope.KvKey)
    ImText("Value: "); ImSameLine()
    ImInputText("##value_kv_input", Scope.KvValue)

    if ImButton("Get value") then
        Scope.KvValue.str = Jila_Kv_Get(
            Scope.KvData, Scope.KvKey.str
        )
    end

    ImSameLine()

    if ImButton("Update value") then
        Jila_Kv_Set(
            Scope.KvData, Scope.KvKey.str,
            Scope.KvValue.str
        )
    end

    ImSameLine()

    if ImButton("Delete value") then
        Jila_Kv_Delete(
            Scope.KvData, Scope.KvKey.str
        )
    end

end

return M -- Required!!!

