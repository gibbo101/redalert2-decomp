// int __stdcall Skirmish_Dialog_Proc(HWND window, UINT message, WPARAM wparam, LPARAM lparam) (0x00683D10)
// The common dialog handler first; then the map preview paint, commands, message 0x497 and the tool tips
// of the player-type, side and colour combo boxes.
#include "shared/skirmish.hpp"
#include "shared/gdlg_supp.hpp"
#include "shared/ms_message_box.hpp"
#include "shared/map_preview.hpp"
#include "shared/owner_draw_dialog_control.hpp"
#include "shared/string_table.hpp"
// @ref ?unknown_dialog_proc_5ffb00@@YIHPAUHWND__@@IIJ@Z=005ffb00
// @ref ?Skirmish_Command@@YIXPAUHWND__@@H0H@Z=006829f0
// @ref ?Skirmish_Message_497@@YIHPAUHWND__@@IJ@Z=00683fc0
// @ref ?unknown_5e4720@OwnerDraw@@YI_NPAUHWND__@@@Z=005e4720
// @ref ?Draw_0061D460@UnknownPreview_0061D430@@QAEXPAUHWND__@@@Z=0061d460
// @ref ?unknown_dialog_preview_a72ce8@@3PAVUnknownPreview_0061D430@@A=00a72ce8
// @ref ?Side_Combo_Player_4d13b0@@YIHH@Z=004d13b0
// @ref ?Color_Combo_Player_4d1d10@@YIHH@Z=004d1d10
// @ref ?Side_Name_4d1420@@YIPBGH@Z=004d1420
// @ref ?Color_Name_4d1d80@@YIPBGH@Z=004d1d80
// @ref ?Side_Combo_Data_4d1c70@@YIHPAUHWND__@@HH@Z=004d1c70
// @ref ?Color_Combo_Data_4d2900@@YIHPAUHWND__@@HH@Z=004d2900
// @ref ??_C@_0BE@OMOF@D?3?2Ra2?2Skirmish?4cpp?$AA@=007f3fd4
// @ref ??_C@_0P@IOHO@STT?3PlayerNone?$AA@=007f3fc4
// @ref ??_C@_0BB@FAHH@STT?3PlayerDumbAI?$AA@=007e7378
// @ref ??_C@_0BC@LDDH@STT?3PlayerSmartAI?$AA@=007e7364
// @ref ??_C@_0BD@PLEH@STT?3PlayerGeniusAI?$AA@=007e7350

int __stdcall Skirmish_Dialog_Proc(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
{
    int result = unknown_dialog_proc_5ffb00(window, message, wparam, lparam);
    if (result != 0) {
        return result;
    }
    switch (message) {
    case 0x0F:
        if (unknown_dialog_preview_a72ce8 != 0 && !OwnerDraw::unknown_5e4720(GetDlgItem(window, 0x468))) {
            unknown_dialog_preview_a72ce8->Draw_0061D460(window);
        }
        ValidateRect(window, 0);
        return 0;
    case 0x111:
        Skirmish_Command(window, wparam & 0xFFFF, (HWND)lparam, wparam >> 16);
        return 1;
    case 0x497:
        return Skirmish_Message_497(window, wparam, lparam);
    case 0x4E9: {
        ToolTipTextRequest *request = (ToolTipTextRequest *)lparam;
        request->Text = 0;
        if (request->Window == 0 || request->Item == -1) {
            return 1;
        }
        int id = GetDlgCtrlID(request->Window);
        if (Skirmish_Player_Index(id) == -1) {
            if (Side_Combo_Player_4d13b0(id) == -1) {
                if (Color_Combo_Player_4d1d10(id) == -1) {
                    return 1;
                }
                request->Text = Color_Name_4d1d80(Color_Combo_Data_4d2900(window, id, request->Item));
                return 1;
            }
            int side = Side_Combo_Data_4d1c70(window, id, request->Item);
            if (side == -1) {
                return 1;
            }
            request->Text = Side_Name_4d1420(side);
            return 1;
        }
        int item = request->Item;
        if (item == -1) {
            item = SendDlgItemMessageA(window, id, CB_GETCURSEL, 0, 0);
        }
        request->Text = Skirmish_Player_Type_Name(SendDlgItemMessageA(window, id, CB_GETITEMDATA, item, 0));
        return 1;
    }
    }
    return 0;
}
