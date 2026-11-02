// Main game-window message dispatcher (WinStub.cpp).
#include "shared/win_stub.hpp"
#include "shared/win_util.hpp"
#include "shared/map_view.hpp"
#include "shared/tool_tip.hpp"
#include "shared/wwmouse.hpp"
#include "shared/winsock_interface.hpp"
#include "shared/movie.hpp"
#include "shared/movie_globals.hpp"
#include "shared/exit.hpp"
extern CCToolTip *ToolTips;
bool __fastcall unknown_moving_736d80(HWND window, unsigned int message, long lparam);
// @ref ?WWKeyboard@@3PAVWWKeyboardClass@@A=00832468
// @ref ?Message_Handler@WWKeyboardClass@@QAEHPAUHWND__@@IIJ@Z=00532a60
extern bool window_mouse_wheel_b263e9;
extern bool window_scroll_coasting_8373fc;
extern bool unknown_redraw_8523dc;
extern char const ime_processed_007fd18c[], focus_gained_007fd170[], focus_lost_007fd180[];
extern char const sidebar_down_007dd0f8[], sidebar_up_007dcf9c[];
void __fastcall Execute_Command_By_Name(char const *name);
extern "C" unsigned int __cdecl wcslen(wchar_t const *text);
unsigned short __fastcall Char_To_Wide_00738130(unsigned int character);
LRESULT WINAPI Windows_Procedure(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
{
    if (PacketTransport && (message == PacketTransport->unknown_slot14(-1) || message == 0x475)) {
        if (PacketTransport->unknown_slot16((int)window, message, wparam, lparam))
            return DefWindowProcA(window, message, wparam, lparam);
        return 0;
    }
    Map.Unknown_0066A400(window, message, wparam, lparam);
    if (MainWindow) GetMenu(MainWindow);
    if (IME_Process_Message(window, message, wparam, lparam)) {
        Debug_Printf(ime_processed_007fd18c);
        return IMEDefaultResult;
    }
    switch (message) {
    case 0x18:
        return 0;
    case 0xf:
        if (unknown_int_a40d48 == 0 && (unknown_flag_a40d28 == true || unknown_flag_851cb0 == true)
            && WWMouse && unknown_surface_839950 && unknown_surface_839954 && unknown_surface_839964) {
            if (unknown_flag_a40d04 == true) {
                Unknown_004E0C90(WWMouse->Is_Captured(), unknown_surface_839964, 0);
                Map.Unknown_0067D420(true);
                ValidateRect(window, 0);
                break;
            }
            if ((unsigned char)Is_Movie_Active()) {
                Movie_Handle_Blit();
                ValidateRect(window, 0);
                break;
            }
            Unknown_004E0C90(WWMouse->Is_Captured(), unknown_surface_839954, 0);
        }
        ValidateRect(window, 0);
        break;
    case 0x14:
        return 1;
    case 1:
        ToolTips = new CCToolTip(window);
        break;
    case 3:
        if (unknown_flag_851cb0 == true && WWMouse)
            static_cast<WWMouseClass *>(WWMouse)->Calc_Confining_Rect();
        break;
    case 2:
        if (ToolTips) {
            delete ToolTips;
            ToolTips = 0;
        }
        MainWindow = 0;
        if (ReadyToQuit != 0) ReadyToQuit = 2;
        return 0;
    case 0x1c:
        if (window == MainWindow && unknown_flag_a40d28 != (wparam != 0)) {
            unknown_flag_a40d28 = wparam != 0;
            if (!unknown_flag_a40d28) {
                Focus_Loss();
                Debug_Printf(focus_lost_007fd180);
            } else {
                Focus_Restore();
                Debug_Printf(focus_gained_007fd170);
            }
            unknown_redraw_8523dc = true;
        }
        return 0;
    case 0x205:
        window_scroll_coasting_8373fc = false;
        break;
    case 0x216:
        return unknown_moving_736d80(window, wparam, lparam);
    case 0x20a:
        if (!window_mouse_wheel_b263e9) {
            window_mouse_wheel_b263e9 = true;
            Execute_Command_By_Name((short)(wparam >> 16) < 0 ? sidebar_down_007dd0f8 : sidebar_up_007dcf9c);
            window_mouse_wheel_b263e9 = false;
        }
        break;
    case 0x112:
        switch (wparam) {
        case 0xf060: return 0;
        case 0xf140: return 0;
        }
        break;
    }
    if (WWKeyboard->Message_Handler(window, message, wparam, lparam)) return 0;
    if (message == 0x286) {
        int index = wcslen(IMEResultString);
        IMEResultString[index] = Char_To_Wide_00738130(wparam);
        IMEResultString[index + 1] = 0;
        return 0;
    }
    return DefWindowProcA(window, message, wparam, lparam);
}
// @ref ?ime_processed_007fd18c@@3QBDB=007fd18c
// @ref ?focus_gained_007fd170@@3QBDB=007fd170
// @ref ?focus_lost_007fd180@@3QBDB=007fd180
// @ref ?sidebar_down_007dd0f8@@3QBDB=007dd0f8
// @ref ?sidebar_up_007dcf9c@@3QBDB=007dcf9c
// @ref ?window_mouse_wheel_b263e9@@3_NA=00b263e9
// @ref ?window_scroll_coasting_8373fc@@3_NA=008373fc
// @ref ?unknown_redraw_8523dc@@3_NA=008523dc
// @ref ?Unknown_0066A400@ScrollClass@@QAEXPAUHWND__@@AAI1AAJ@Z=0066a400
// @ref ?Unknown_0067D420@SidebarClass@@QAEX_N@Z=0067d420
// @ref ?unknown_moving_736d80@@YI_NPAUHWND__@@IJ@Z=00736d80
// @ref ?Execute_Command_By_Name@@YIXPBD@Z=00519480
// @ref _wcslen=00783605
// @ref ??0ToolTipManager@@QAE@PAUHWND__@@@Z=006eb2e0
// @ref ??2@YAPAXI@Z=00782017
// @ref ??_7CCToolTip@@6B@=007af51c
// @ref ??_C@_04NCCD@true?$AA@=007d24d8
// @ref ??_C@_05NAGO@false?$AA@=007d24d0
// @ref ??_C@_0CD@PHED@Focus_Loss?$CI?$CJ?3?5_MouseCaptured?5?$DN?5?$CF@=007fd0e4
// @ref ??_C@_0O@GJFN@Focus_Loss?$CI?$CJ?6?$AA@=007fd108
// @ref ?Calc_Confining_Rect@WWMouseClass@@QAEXXZ=00771c50
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ?Focus_Restore@@YAXXZ=00737400
// @ref ?IMEDefaultResult@@3JA=00b263f8
// @ref ?IMEResultString@@3PAGA=00b25f7c
// @ref ?IME_Process_Message@@YIHPAUHWND__@@IIJ@Z=00737fc0
// @ref ?Is_Movie_Active@@YIHXZ=005a1ed0
// @ref ?MainWindow@@3PAUHWND__@@A=00b263d8
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Movie_Handle_Blit@@YIXXZ=005a1ef0
// @ref ?PacketTransport@@3PAVWinsockInterfaceClass@@A=00839c50
// @ref ?Pause_Radar_Movie_005a0a90@@YIX_N@Z=005a0a90
// @ref ?ReadyToQuit@@3HA=00a40d80
// @ref ?ToolTips@@3PAVCCToolTip@@A=008399b0
// @ref ?Unknown_00406F50@@YAXXZ=00406f50
// @ref ?Unknown_004E0C90@@YIX_NPAVSurface@@H@Z=004e0c90
// @ref ?WWMouse@@3PAVMouse@@A=00839c68
// @ref ?unknown_flag_851cb0@@3_NA=00851cb0
// @ref ?unknown_flag_a40d04@@3_NA=00a40d04
// @ref ?unknown_flag_a40d28@@3_NA=00a40d28
// @ref ?unknown_int_a40d48@@3HA=00a40d48
// @ref ?unknown_mouse_captured_b263e8@@3_NA=00b263e8
// @ref ?unknown_surface_839950@@3PAVSurface@@A=00839950
// @ref ?unknown_surface_839954@@3PAVSurface@@A=00839954
// @ref ?unknown_surface_839964@@3PAVSurface@@A=00839964
// @ref __imp__DefWindowProcA@16=0079a388
// @ref __imp__GetMenu@4=0079a390
// @ref __imp__MultiByteToWideChar@24=0079a1b8
// @ref __imp__ValidateRect@8=0079a3f8
