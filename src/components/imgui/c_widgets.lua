---@meta c_widgets

---@param label string
---@return boolean
---
---@overload fun(label: string, size: ImVec2): boolean
function Button(label) end

---@param text string
function Text(text) end

---@param text string
function TextWrapped(text) end

--- @param label string
--- @param preview string
---
--- @return boolean
---
--- @overload fun(label: string, preview: string, flags: integer): boolean
function BeginCombo(label, preview) end

--- @param label string
--- @param opened BoolProperty
---
--- @return boolean
---
--- @overload fun(label: string, opened: BoolProperty, flags: integer): boolean
--- @overload fun(label: string, opened: BoolProperty, flags: integer, size: ImVec2): boolean
function Selectable(label, opened) end

function EndCombo() end

---@return boolean
function BeginMenuBar() end

---@return boolean
function BeginMainMenuBar() end

--- @param label string
---
--- @return boolean
function BeginMenu(label) end

---@param label string
---
---@return boolean
---
---@overload fun(label: string, selected: BoolProperty): boolean
---@overload fun(label: string, shortcut: string, selected: BoolProperty): boolean
function MenuItem(label) end

function EndMenu() end

function EndMenuBar() end

function EndMainMenuBar() end

---@param label string
---
---@return boolean
function BeginTabBar(label) end

---@param label string
---
---@return boolean
function BeginTabItem(label) end

function EndTabItem() end

function EndTabBar() end

---@param label string
---@param prop BoolProperty
---
---@return boolean
function Checkbox(label, prop) end

---@param label string
function OpenPopup(label) end

---@param label string
---
---@return boolean
---
---@overload fun(label: string, opened: BoolProperty): boolean
function BeginModal(label) end

function EndModal() end

---@param str_id string
---@param column integer
---@return boolean
function BeginTable(str_id, column) end

function EndTable() end

function TableNextRow() end

---@return boolean
function TableNextColumn() end

---@param label string
function TableSetupColumn(label) end

function TableHeadersRow() end

---@param label string
---
---@return boolean
function TreeNode(label, opened) end

function TreePop() end

---@param label string
---
---@return boolean
---
---@overload fun(label: string, opened: BoolProperty): boolean
---@overload fun(label: string, opened: BoolProperty, flags: integer): boolean
function CollapsingHeader(label) end

---@param fraction number
function ProgressBar(fraction) end

---@param fraction number
---@param size ImVec2
function ProgressBar(fraction, size) end

function Bullet() end
