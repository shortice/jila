/*
Flags.
*/
#include "imgui.h"
#include "components/imgui/c_flags.hpp"

namespace Jila {

void bindImFlags(sol::state* state) {
    (*state)["ImGuiCol_Text"] = ImGuiCol_Text;
    (*state)["ImGuiCol_TextDisabled"] = ImGuiCol_TextDisabled;
    (*state)["ImGuiCol_WindowBg"] = ImGuiCol_WindowBg;
    (*state)["ImGuiCol_ChildBg"] = ImGuiCol_ChildBg;
    (*state)["ImGuiCol_PopupBg"] = ImGuiCol_PopupBg;
    (*state)["ImGuiCol_Border"] = ImGuiCol_Border;
    (*state)["ImGuiCol_BorderShadow"] = ImGuiCol_BorderShadow;
    (*state)["ImGuiCol_FrameBg"] = ImGuiCol_FrameBg;
    (*state)["ImGuiCol_FrameBgHovered"] = ImGuiCol_FrameBgHovered;
    (*state)["ImGuiCol_FrameBgActive"] = ImGuiCol_FrameBgActive;
    (*state)["ImGuiCol_TitleBg"] = ImGuiCol_TitleBg;
    (*state)["ImGuiCol_TitleBgActive"] = ImGuiCol_TitleBgActive;
    (*state)["ImGuiCol_TitleBgCollapsed"] = ImGuiCol_TitleBgCollapsed;
    (*state)["ImGuiCol_MenuBarBg"] = ImGuiCol_MenuBarBg;
    (*state)["ImGuiCol_ScrollbarBg"] = ImGuiCol_ScrollbarBg;
    (*state)["ImGuiCol_ScrollbarGrab"] = ImGuiCol_ScrollbarGrab;
    (*state)["ImGuiCol_ScrollbarGrabHovered"] = ImGuiCol_ScrollbarGrabHovered;
    (*state)["ImGuiCol_ScrollbarGrabActive"] = ImGuiCol_ScrollbarGrabActive;
    (*state)["ImGuiCol_CheckMark"] = ImGuiCol_CheckMark;
    (*state)["ImGuiCol_SliderGrab"] = ImGuiCol_SliderGrab;
    (*state)["ImGuiCol_SliderGrabActive"] = ImGuiCol_SliderGrabActive;
    (*state)["ImGuiCol_Button"] = ImGuiCol_Button;
    (*state)["ImGuiCol_ButtonHovered"] = ImGuiCol_ButtonHovered;
    (*state)["ImGuiCol_ButtonActive"] = ImGuiCol_ButtonActive;
    (*state)["ImGuiCol_Header"] = ImGuiCol_Header;
    (*state)["ImGuiCol_HeaderHovered"] = ImGuiCol_HeaderHovered;
    (*state)["ImGuiCol_HeaderActive"] = ImGuiCol_HeaderActive;
    (*state)["ImGuiCol_Separator"] = ImGuiCol_Separator;
    (*state)["ImGuiCol_SeparatorHovered"] = ImGuiCol_SeparatorHovered;
    (*state)["ImGuiCol_SeparatorActive"] = ImGuiCol_SeparatorActive;
    (*state)["ImGuiCol_ResizeGrip"] = ImGuiCol_ResizeGrip;
    (*state)["ImGuiCol_ResizeGripHovered"] = ImGuiCol_ResizeGripHovered;
    (*state)["ImGuiCol_ResizeGripActive"] = ImGuiCol_ResizeGripActive;
    (*state)["ImGuiCol_InputTextCursor"] = ImGuiCol_InputTextCursor;
    (*state)["ImGuiCol_TabHovered"] = ImGuiCol_TabHovered;
    (*state)["ImGuiCol_Tab"] = ImGuiCol_Tab;
    (*state)["ImGuiCol_TabSelected"] = ImGuiCol_TabSelected;
    (*state)["ImGuiCol_TabSelectedOverline"] = ImGuiCol_TabSelectedOverline;
    (*state)["ImGuiCol_TabDimmed"] = ImGuiCol_TabDimmed;
    (*state)["ImGuiCol_TabDimmedSelected"] = ImGuiCol_TabDimmedSelected;
    (*state)["ImGuiCol_TabDimmedSelectedOverline"] = ImGuiCol_TabDimmedSelectedOverline;
    (*state)["ImGuiCol_PlotLines"] = ImGuiCol_PlotLines;
    (*state)["ImGuiCol_PlotLinesHovered"] = ImGuiCol_PlotLinesHovered;
    (*state)["ImGuiCol_PlotHistogram"] = ImGuiCol_PlotHistogram;
    (*state)["ImGuiCol_PlotHistogramHovered"] = ImGuiCol_PlotHistogramHovered;
    (*state)["ImGuiCol_TableHeaderBg"] = ImGuiCol_TableHeaderBg;
    (*state)["ImGuiCol_TableBorderStrong"] = ImGuiCol_TableBorderStrong;
    (*state)["ImGuiCol_TableBorderLight"] = ImGuiCol_TableBorderLight;
    (*state)["ImGuiCol_TableRowBg"] = ImGuiCol_TableRowBg;
    (*state)["ImGuiCol_TableRowBgAlt"] = ImGuiCol_TableRowBgAlt;
    (*state)["ImGuiCol_TextLink"] = ImGuiCol_TextLink;
    (*state)["ImGuiCol_TextSelectedBg"] = ImGuiCol_TextSelectedBg;
    (*state)["ImGuiCol_TreeLines"] = ImGuiCol_TreeLines;
    (*state)["ImGuiCol_DragDropTarget"] = ImGuiCol_DragDropTarget;
    (*state)["ImGuiCol_NavCursor"] = ImGuiCol_NavCursor;
    (*state)["ImGuiCol_NavWindowingHighlight"] = ImGuiCol_NavWindowingHighlight;
    (*state)["ImGuiCol_NavWindowingDimBg"] = ImGuiCol_NavWindowingDimBg;
    (*state)["ImGuiCol_ModalWindowDimBg"] = ImGuiCol_ModalWindowDimBg;

    // ImGuiTreeNodeFlags
    (*state)["ImGuiTreeNodeFlags_None"] = ImGuiTreeNodeFlags_None;
    (*state)["ImGuiTreeNodeFlags_Selected"] = ImGuiTreeNodeFlags_Selected;
    (*state)["ImGuiTreeNodeFlags_Framed"] = ImGuiTreeNodeFlags_Framed;
    (*state)["ImGuiTreeNodeFlags_AllowOverlap"] = ImGuiTreeNodeFlags_AllowOverlap;
    (*state)["ImGuiTreeNodeFlags_NoTreePushOnOpen"] = ImGuiTreeNodeFlags_NoTreePushOnOpen;
    (*state)["ImGuiTreeNodeFlags_NoOpenOnArrow"] = ImGuiTreeNodeFlags_OpenOnArrow;
    (*state)["ImGuiTreeNodeFlags_NoOpenOnDoubleClick"] = ImGuiTreeNodeFlags_OpenOnDoubleClick;
    (*state)["ImGuiTreeNodeFlags_Leaf"] = ImGuiTreeNodeFlags_Leaf;
    (*state)["ImGuiTreeNodeFlags_Bullet"] = ImGuiTreeNodeFlags_Bullet;
    (*state)["ImGuiTreeNodeFlags_FramePadding"] = ImGuiTreeNodeFlags_FramePadding;
    (*state)["ImGuiTreeNodeFlags_SpanAvailWidth"] = ImGuiTreeNodeFlags_SpanAvailWidth;
    (*state)["ImGuiTreeNodeFlags_SpanFullWidth"] = ImGuiTreeNodeFlags_SpanFullWidth;
    (*state)["ImGuiTreeNodeFlags_NavLeftJumpsBackHere"] = ImGuiTreeNodeFlags_NavLeftJumpsBackHere;

    // ImGuiSliderFlags
    (*state)["ImGuiSliderFlags_None"] = ImGuiSliderFlags_None;
    (*state)["ImGuiSliderFlags_Logarithmic"] = ImGuiSliderFlags_Logarithmic;
    (*state)["ImGuiSliderFlags_NoRoundToFormat"] = ImGuiSliderFlags_NoRoundToFormat;
    (*state)["ImGuiSliderFlags_NoInput"] = ImGuiSliderFlags_NoInput;
    (*state)["ImGuiSliderFlags_ClampOnInput"] = ImGuiSliderFlags_ClampOnInput;

    // ImGuiColorEditFlags
    (*state)["ImGuiColorEditFlags_None"] = ImGuiColorEditFlags_None;
    (*state)["ImGuiColorEditFlags_NoAlpha"] = ImGuiColorEditFlags_NoAlpha;
    (*state)["ImGuiColorEditFlags_NoPicker"] = ImGuiColorEditFlags_NoPicker;
    (*state)["ImGuiColorEditFlags_NoOptions"] = ImGuiColorEditFlags_NoOptions;
    (*state)["ImGuiColorEditFlags_NoSmallPreview"] = ImGuiColorEditFlags_NoSmallPreview;
    (*state)["ImGuiColorEditFlags_NoInputs"] = ImGuiColorEditFlags_NoInputs;
    (*state)["ImGuiColorEditFlags_NoTooltip"] = ImGuiColorEditFlags_NoTooltip;
    (*state)["ImGuiColorEditFlags_NoLabel"] = ImGuiColorEditFlags_NoLabel;
    (*state)["ImGuiColorEditFlags_NoDragDrop"] = ImGuiColorEditFlags_NoDragDrop;
    (*state)["ImGuiColorEditFlags_NoBorder"] = ImGuiColorEditFlags_NoBorder;

    // ImGuiStyleVar
    (*state)["ImGuiStyleVar_Alpha"] = ImGuiStyleVar_Alpha;
    (*state)["ImGuiStyleVar_WindowPadding"] = ImGuiStyleVar_WindowPadding;
    (*state)["ImGuiStyleVar_WindowRounding"] = ImGuiStyleVar_WindowRounding;
    (*state)["ImGuiStyleVar_WindowBorderSize"] = ImGuiStyleVar_WindowBorderSize;
    (*state)["ImGuiStyleVar_WindowMinSize"] = ImGuiStyleVar_WindowMinSize;
    (*state)["ImGuiStyleVar_WindowTitleAlign"] = ImGuiStyleVar_WindowTitleAlign;

    // ImGuiMouseButton
    (*state)["ImGuiMouseButton_Left"] = ImGuiMouseButton_Left;
    (*state)["ImGuiMouseButton_Right"] = ImGuiMouseButton_Right;
    (*state)["ImGuiMouseButton_Middle"] = ImGuiMouseButton_Middle;

    // ImGuiKey
    (*state)["ImGuiKey_Tab"] = ImGuiKey_Tab;
    (*state)["ImGuiKey_LeftArrow"] = ImGuiKey_LeftArrow;
    (*state)["ImGuiKey_RightArrow"] = ImGuiKey_RightArrow;
    (*state)["ImGuiKey_UpArrow"] = ImGuiKey_UpArrow;
    (*state)["ImGuiKey_DownArrow"] = ImGuiKey_DownArrow;
    (*state)["ImGuiKey_PageUp"] = ImGuiKey_PageUp;
    (*state)["ImGuiKey_PageDown"] = ImGuiKey_PageDown;
    (*state)["ImGuiKey_Home"] = ImGuiKey_Home;
    (*state)["ImGuiKey_End"] = ImGuiKey_End;
    (*state)["ImGuiKey_Insert"] = ImGuiKey_Insert;
    (*state)["ImGuiKey_Delete"] = ImGuiKey_Delete;
    (*state)["ImGuiKey_Backspace"] = ImGuiKey_Backspace;
    (*state)["ImGuiKey_Space"] = ImGuiKey_Space;
    (*state)["ImGuiKey_Enter"] = ImGuiKey_Enter;
    (*state)["ImGuiKey_Escape"] = ImGuiKey_Escape;
    (*state)["ImGuiKey_KeyPadEnter"] = ImGuiKey_KeypadEnter;
    (*state)["ImGuiKey_A"] = ImGuiKey_A;
    (*state)["ImGuiKey_C"] = ImGuiKey_C;
    (*state)["ImGuiKey_V"] = ImGuiKey_V;
    (*state)["ImGuiKey_X"] = ImGuiKey_X;
    (*state)["ImGuiKey_Y"] = ImGuiKey_Y;
    (*state)["ImGuiKey_Z"] = ImGuiKey_Z;

    // ImGuiWindowFlags
    (*state)["ImGuiWindowFlags_None"] = ImGuiWindowFlags_None;
    (*state)["ImGuiWindowFlags_NoTitleBar"] = ImGuiWindowFlags_NoTitleBar;
    (*state)["ImGuiWindowFlags_NoResize"] = ImGuiWindowFlags_NoResize;
    (*state)["ImGuiWindowFlags_NoMove"] = ImGuiWindowFlags_NoMove;
    (*state)["ImGuiWindowFlags_NoScrollbar"] = ImGuiWindowFlags_NoScrollbar;
    (*state)["ImGuiWindowFlags_NoScrollWithMouse"] = ImGuiWindowFlags_NoScrollWithMouse;
    (*state)["ImGuiWindowFlags_NoCollapse"] = ImGuiWindowFlags_NoCollapse;
    (*state)["ImGuiWindowFlags_AlwaysAutoResize"] = ImGuiWindowFlags_AlwaysAutoResize;
    (*state)["ImGuiWindowFlags_NoBackground"] = ImGuiWindowFlags_NoBackground;
    (*state)["ImGuiWindowFlags_NoSavedSettings"] = ImGuiWindowFlags_NoSavedSettings;
    (*state)["ImGuiWindowFlags_NoMouseInputs"] = ImGuiWindowFlags_NoMouseInputs;
    (*state)["ImGuiWindowFlags_MenuBar"] = ImGuiWindowFlags_MenuBar;
    (*state)["ImGuiWindowFlags_HorizontalScrollbar"] = ImGuiWindowFlags_HorizontalScrollbar;
    (*state)["ImGuiWindowFlags_NoFocusOnAppearing"] = ImGuiWindowFlags_NoFocusOnAppearing;
    (*state)["ImGuiWindowFlags_NoBringToFrontOnFocus"] = ImGuiWindowFlags_NoBringToFrontOnFocus;
    (*state)["ImGuiWindowFlags_AlwaysHorizontalScrollbar"] = ImGuiWindowFlags_AlwaysHorizontalScrollbar;
    (*state)["ImGuiWindowFlags_AlwaysVerticalScrollbar"] = ImGuiWindowFlags_AlwaysVerticalScrollbar;
    (*state)["ImGuiWindowFlags_AlwaysUseWindowPadding"] = ImGuiWindowFlags_AlwaysUseWindowPadding;
    (*state)["ImGuiWindowFlags_NoNavInputs"] = ImGuiWindowFlags_NoNavInputs;
    (*state)["ImGuiWindowFlags_NoNavFocus"] = ImGuiWindowFlags_NoNavFocus;
    (*state)["ImGuiWindowFlags_NoNav"] = ImGuiWindowFlags_NoNav;
    (*state)["ImGuiWindowFlags_NoDecoration"] = ImGuiWindowFlags_NoDecoration;
    (*state)["ImGuiWindowFlags_NoInputs"] = ImGuiWindowFlags_NoInputs;
    (*state)["ImGuiWindowFlags_NavFlattened"] = ImGuiWindowFlags_NavFlattened;
    (*state)["ImGuiWindowFlags_UnsavedDocument"] = ImGuiWindowFlags_UnsavedDocument;

    // ImGuiChildFlags
    (*state)["ImGuiChildFlags_None"] = ImGuiChildFlags_None;
    (*state)["ImGuiChildFlags_Borders"] = ImGuiChildFlags_Borders;
    (*state)["ImGuiChildFlags_AlwaysUseWindowPadding"] = ImGuiChildFlags_AlwaysUseWindowPadding;
    (*state)["ImGuiChildFlags_ResizeX"] = ImGuiChildFlags_ResizeX;
    (*state)["ImGuiChildFlags_ResizeY"] = ImGuiChildFlags_ResizeY;
    (*state)["ImGuiChildFlags_AutoResizeX"] = ImGuiChildFlags_AutoResizeX;
    (*state)["ImGuiChildFlags_AutoResizeY"] = ImGuiChildFlags_AutoResizeY;
    (*state)["ImGuiChildFlags_FrameStyle"] = ImGuiChildFlags_FrameStyle;
}

}
