// int __stdcall Faction_Select_Dialog_Proc_007689c0(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
// (0x007689C0): the World Domination Tour faction dialog's procedure. WM_INITDIALOG keeps the
// FactionSelectDialogControl as the DWL_USER value; then the common handler 0x005FFB00. The control
// tracks the cursor (0x84), paints its image, ends the dialog on button 0x686 (-1) or a click on a
// faction (1), and answers the tool tip request (0x4E9) for the faction under the cursor.
#include "shared/wdt_faction_select.hpp"
#include "shared/surface.hpp"
#include "shared/rect.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/campaign_score.hpp"
#include "shared/ms_message_box.hpp"
#include "shared/skirmish.hpp"
#include "shared/string_table.hpp"
#include "shared/wide_string.hpp"

// @ref __imp__SetWindowLongA@12=0079a488
// @ref __imp__GetWindowLongA@8=0079a48c
// @ref __imp__ValidateRect@8=0079a3f8
// @ref ?unknown_dialog_proc_5ffb00@@YIHPAUHWND__@@IIJ@Z=005ffb00
// @ref ??_C@_0BE@OCMA@D?3?2Ra2?2WorldDom?4cpp?$AA@=00800558
// @ref ??_C@_0BJ@ODIK@WDT?3FactionSelectToolTip?$AA@=007e9388
// @ref ??_C@_0BP@GNCD@WDT?3FactionSelectAlliesToolTip?$AA@=00800518
// @ref ??_C@_0BP@LOEN@WDT?3FactionSelectSovietToolTip?$AA@=00800538
// @ref ?Mouse_Move_00768840@FactionSelectDialogControl@WorldDominationTour@@QAEXPAUHWND__@@ABUPoint2D@@@Z=00768840

int __stdcall Faction_Select_Dialog_Proc_007689c0(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
{
    if (message == 0x110 && lparam != 0) {
        SetWindowLongA(window, 8, ((UnknownDialogCreateParam *)lparam)->Param);
    }
    int result = unknown_dialog_proc_5ffb00(window, message, wparam, lparam);
    if (result != 0) {
        return result;
    }
    WorldDominationTour::FactionSelectDialogControl *control = (WorldDominationTour::FactionSelectDialogControl *)GetWindowLongA(window, 8);
    switch (message) {
        case 0x84: {
            Point2D point(lparam & 0xFFFF, (unsigned int)lparam >> 16);
            control->Mouse_Move_00768840(window, point);
            return 0;
        }
        case 0x2B:
            Unknown_005FE380(lparam);
            return 1;
        case 0x0F:
            Unknown_005FEE70(window);
            control->Draw_00768940(0);
            unknown_dialog_5e5f20(window);
            ValidateRect(window, 0);
            return 1;
        case 0x14:
            return 1;
        case 0x111:
            if ((unsigned short)wparam == 0x686) {
                control->Set_Window_006010f0((unsigned int)window, (HWND)-1);
                return 0;
            }
            break;
        case 0x497:
            return 0;
        case 0x4E9: {
            ToolTipTextRequest *request = (ToolTipTextRequest *)lparam;
            if (request->Window == window) {
                wchar_t const *text;
                switch (control->Selection) {
                    case 2:
                        text = StringTable::Load_String("WDT:FactionSelectAlliesToolTip", 0, "D:\\Ra2\\WorldDom.cpp", 176);
                        break;
                    case 3:
                        text = StringTable::Load_String("WDT:FactionSelectSovietToolTip", 0, "D:\\Ra2\\WorldDom.cpp", 179);
                        break;
                    default:
                        text = StringTable::Load_String("WDT:FactionSelectToolTip", 0, "D:\\Ra2\\WorldDom.cpp", 182);
                        break;
                }
                WideString string(text);
                request->Text = string;
            }
            return 0;
        }
        case 0x202:
            if (control->Selection != 0) {
                control->Set_Window_006010f0((unsigned int)window, (HWND)1);
            }
            break;
    }
    return 0;
}
