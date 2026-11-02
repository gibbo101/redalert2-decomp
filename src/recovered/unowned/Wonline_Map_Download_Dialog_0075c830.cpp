// Wonline_Map_Download_Dialog0075C830: preview and progress while waiting.
#include "shared/dialog_default_proc.hpp"
#include "shared/map_preview.hpp"
#include "shared/progress_screen.hpp"
#include "shared/unknown_globals.hpp"
extern HANDLE wol_wait_events_b264f8[18];
void __fastcall unknown_dialog_5e5f20(HWND window);
int __stdcall Wonline_Map_Download_Dialog_0075c830(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
{
    int result = unknown_dialog_proc_5ffb00(window, message, wparam, lparam);
    if (result != 0) return result;
    if (message <= 0x2b) {
        if (message != 0x2b) {
        switch (message) {
    case 2:
        if (unknown_dialog_preview_a72ce8) {
            delete unknown_dialog_preview_a72ce8;
            unknown_dialog_preview_a72ce8 = 0;
            return 0;
        }
        break;
    case 0xf: {
        Unknown_005FEE70(window);
        unknown_dialog_5e5f20(window);
        UnknownPreview_0061D430 *preview = unknown_dialog_preview_a72ce8;
        if (!preview && unknown_session_a3d2b4 == -1) preview = unknown_preview_a6fee4;
        if (preview) preview->Draw_0061D460(window);
        if (ProgressScreen.Has_Window()) ProgressScreen.Draw_It(Point2D(-1, -1));
        ValidateRect(window, 0);
        return 1;
    }
    case 0x14:
        return 1;
        }
        } else {
            Unknown_005FE380(lparam);
            return 1;
        }
    } else if (message == 0x111) {
        if ((unsigned short)wparam == 0x5c0) {
            SetEvent(wol_wait_events_b264f8[0]);
            Unknown_007357E0(window, 0x5c0);
        }
    }
    return 0;
}
// @ref ?wol_wait_events_b264f8@@3PAPAXA=00b264f8
// @ref ??1UnknownPreview_0061D430@@QAE@XZ=0061d440
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ?Draw_0061D460@UnknownPreview_0061D430@@QAEXPAUHWND__@@@Z=0061d460
// @ref ?Draw_It@ProgressScreenClass@@QAEXUPoint2D@@@Z=00620050
// @ref ?Has_Window@ProgressScreenClass@@QAE_NXZ=006203c0
// @ref ?ProgressScreen@@3VProgressScreenClass@@A=00a769e8
// @ref ?Unknown_005FE380@@YIXJ@Z=005fe380
// @ref ?Unknown_005FEE70@@YIXPAUHWND__@@@Z=005fee70
// @ref ?Unknown_007357E0@@YIXPAXH@Z=007357e0
// @ref ?unknown_dialog_5e5f20@@YIXPAUHWND__@@@Z=005e5f20
// @ref ?unknown_dialog_preview_a72ce8@@3PAVUnknownPreview_0061D430@@A=00a72ce8
// @ref ?unknown_dialog_proc_5ffb00@@YIHPAUHWND__@@IIJ@Z=005ffb00
// @ref ?unknown_preview_a6fee4@@3PAVUnknownPreview_0061D430@@A=00a6fee4
// @ref ?unknown_session_a3d2b4@@3HA=00a3d2b4
// @ref __imp__SetEvent@4=0079a234
// @ref __imp__ValidateRect@8=0079a3f8
