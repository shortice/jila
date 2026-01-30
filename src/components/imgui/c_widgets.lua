---@meta c_widgets

---@param label string
---@return boolean
---
---@overload fun(label: string, size: ImVec2): boolean
function ImButton(label) end

---@param text string
function ImText(text) end

---@param text string
function ImTextWrapped(text) end

---@param label string
---@param text CharProperty
---@param size ImVec2
function ImSelectableText(label, text, size) end

--- @param label string
--- @param preview string
---
--- @return boolean
---
--- @overload fun(label: string, preview: string, flags: integer): boolean
function ImBeginCombo(label, preview) end

--- @param label string
--- @param opened BoolProperty
---
--- @return boolean
---
--- @overload fun(label: string, opened: BoolProperty, flags: integer): boolean
--- @overload fun(label: string, opened: BoolProperty, flags: integer, size: ImVec2): boolean
function ImSelectable(label, opened) end

function ImEndCombo() end

---@return boolean
function ImBeginMenuBar() end

---@return boolean
function ImBeginMainMenuBar() end

--- @param label string
---
--- @return boolean
function ImBeginMenu(label) end

---@param label string
---
---@return boolean
---
---@overload fun(label: string, selected: BoolProperty): boolean
---@overload fun(label: string, shortcut: string, selected: BoolProperty): boolean
function ImMenuItem(label) end

function ImEndMenu() end

function ImEndMenuBar() end

function ImEndMainMenuBar() end

---@param label string
---
---@return boolean
function ImBeginTabBar(label) end

---@param label string
---
---@return boolean
function ImBeginTabItem(label) end

function ImEndTabItem() end

function ImEndTabBar() end

---@param label string
---@param prop BoolProperty
---
---@return boolean
function ImCheckbox(label, prop) end

---@param label string
function ImOpenPopup(label) end

---@param label string
---
---@return boolean
---
---@overload fun(label: string, opened: BoolProperty): boolean
function ImBeginModal(label) end

function ImEndModal() end

---@param str_id string
---@param column integer
---@return boolean
function ImBeginTable(str_id, column) end

function ImEndTable() end

function ImTableNextRow() end

---@return boolean
function ImTableNextColumn() end

---@param label string
function ImTableSetupColumn(label) end

function ImTableHeadersRow() end

---@param label string
---
---@return boolean
function ImTreeNode(label, opened) end

function ImTreePop() end

---@param label string
---
---@return boolean
---
---@overload fun(label: string, opened: BoolProperty): boolean
---@overload fun(label: string, opened: BoolProperty, flags: integer): boolean
function ImCollapsingHeader(label) end

---@param fraction FloatProperty
---
---@overload fun(fraction: FloatProperty, size: ImVec2)
function ImProgressBar(fraction) end

function ImBullet() end

---@param label string
---
---@return boolean
function ImBeginListBox(label) end

function ImEndListBox() end

--- @param texture Jila_Texture
--- @param imageSize ImVec2
function ImImage(texture, imageSize) end

--- @param label string
--- @param texture Jila_Texture
--- @param imageSize ImVec2
function ImImageButton(label, texture, imageSize) end
