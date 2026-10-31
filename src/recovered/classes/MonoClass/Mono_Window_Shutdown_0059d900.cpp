// void Mono_Window_Shutdown() (0x0059D900)
// Frees the eight pages, then deletes the font and destroys the dialog.
#include "shared/win32_gdi.hpp"
#include "shared/mono_window.hpp"
// @ref ?unknown_mono_pages_a70e40@@3PAPAVMonoClass@@A=00a70e40
// @ref ?unknown_mono_window_a70f10@@3PAUHWND__@@A=00a70f10
// @ref ?unknown_mono_font_a70f14@@3PAXA=00a70f14
// @ref ?Unknown_Remove_Modeless_Dialog_00522b80@@YIXPAUHWND__@@@Z=00522b80
// @ref __imp__DeleteObject@4=0079a058
// @ref __imp__DestroyWindow@4=0079a3d4
// @ref ??3@YAXPAX@Z=00781d3b

void Mono_Window_Shutdown()
{
    for (int i = 0; i < 8; i++) {
        if (unknown_mono_pages_a70e40[i] != 0) {
            delete unknown_mono_pages_a70e40[i];
            unknown_mono_pages_a70e40[i] = 0;
        }
    }
    if (unknown_mono_window_a70f10 != 0) {
        DeleteObject(unknown_mono_font_a70f14);
        Unknown_Remove_Modeless_Dialog_00522b80(unknown_mono_window_a70f10);
        DestroyWindow(unknown_mono_window_a70f10);
        unknown_mono_font_a70f14 = 0;
        unknown_mono_window_a70f10 = 0;
    }
}
