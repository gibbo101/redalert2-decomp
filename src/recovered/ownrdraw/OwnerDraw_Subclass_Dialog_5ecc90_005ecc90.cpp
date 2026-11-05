// @ref ?unknown_5eac30@OwnerDraw@@YIXXZ=005eac30
// @ref ?unknown_dialog_a763cc@OwnerDraw@@3PAUHWND__@@A=00a763cc
// @ref __imp__EnumChildWindows@12=0079a4dc
// @ref ?unknown_replace_edit_5ecb00@OwnerDraw@@YGHPAUHWND__@@J@Z=005ecb00
// @ref ?unknown_5ed180@OwnerDraw@@YGHPAUHWND__@@J@Z=005ed180
// @ref ?Add@?$WolDictionary@IUUnknownControlRecord@OwnerDraw@@@@QAE_NABIABUUnknownControlRecord@OwnerDraw@@@Z=006014e0
// @ref ??1UnknownControlRecord@OwnerDraw@@QAE@XZ=00600350
// @ref ?Set_Wide_Text_600510@UnknownControlRecord@OwnerDraw@@QAEXPBG@Z=00600510
// @ref ?Get_Pointer@?$WolDictionary@IUUnknownControlRecord@OwnerDraw@@@@QBE_NABIPAPAUUnknownControlRecord@OwnerDraw@@@Z=00601710
// @ref ?Grow_Table@?$WolDictionary@IUUnknownControlRecord@OwnerDraw@@@@QAEXXZ=00601f70
#include "shared/win32_api.hpp"
#include "shared/wide_string.hpp"
#include "shared/wol_dictionary.hpp"
#include "shared/owner_draw_dialog_control.hpp"

namespace OwnerDraw {

BOOL __stdcall unknown_replace_edit_5ecb00(HWND window, LPARAM lparam);
BOOL __stdcall unknown_5ed180(HWND window, LPARAM lparam);
BOOL __stdcall Set_Paint_Disabled_5ecf40(HWND window, LPARAM lparam);

// Subclasses a dialog and its controls (TibSun OwnerDraw::Subclass_Dialog), with painting off meanwhile.
bool __fastcall Subclass_Dialog_5ecc90(HWND window, LPARAM lparam)
{
    unknown_5eac30();
    unknown_dialog_a763cc = window;
    EnumChildWindows(window, Set_Paint_Disabled_5ecf40, 1);
    Set_Paint_Disabled_5ecf40(window, 1);
    EnumChildWindows(window, unknown_replace_edit_5ecb00, 1);
    EnumChildWindows(window, unknown_5ed180, lparam);
    unknown_5ed180(window, lparam);
    EnumChildWindows(window, Set_Paint_Disabled_5ecf40, 0);
    Set_Paint_Disabled_5ecf40(window, 0);
    return true;
}

}
