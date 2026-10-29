// long __stdcall Unknown_Dialog_Proc_005c33a0(HWND window, unsigned message, unsigned wparam, long lparam) (0x005C33A0)
// A plain lobby message dialog's procedure: paints and draws its items, and ends with the command id of
// buttons 1, 2, 6 and 7 (IDOK, IDCANCEL, IDYES, IDNO).
#include "shared/lobby.hpp"
#include "shared/campaign_score.hpp"

long __stdcall Unknown_Dialog_Proc_005c33a0(HWND window, unsigned message, unsigned wparam, long lparam)
{
    switch (message) {
    case 0x14:                  // WM_ERASEBKGND
        return 1;
    case 0x0f:                  // WM_PAINT
        Unknown_005FEE70(window);
        unknown_dialog_5e5f20(window);
        ValidateRect(window, 0);
        return 1;
    case 0x2b:                  // WM_DRAWITEM
        Unknown_005FE380(lparam);
        return 1;
    case 0x111:                 // WM_COMMAND
        switch (wparam & 0xffff) {
        case 1:
        case 2:
        case 6:
        case 7:
            Unknown_007357E0(window, wparam & 0xffff);
            return 1;
        }
        break;
    }
    return 0;
}
