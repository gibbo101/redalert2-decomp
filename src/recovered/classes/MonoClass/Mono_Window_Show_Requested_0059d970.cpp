// void Mono_Window_Show_Requested() (0x0059D970)
// Without a parent window only records the request; otherwise shows the dialog (creating it first).
#include "shared/win32_api.hpp"
#include "shared/mono_window.hpp"
// @ref ?unknown_mono_parent_a70f04@@3PAUHWND__@@A=00a70f04
// @ref ?unknown_mono_allowed_a70f08@@3_NA=00a70f08
// @ref ?unknown_mono_requested_a70f09@@3_NA=00a70f09
// @ref ?unknown_mono_enabled_a70f0a@@3_NA=00a70f0a
// @ref ?unknown_mono_window_a70f10@@3PAUHWND__@@A=00a70f10
// @ref ?Mono_Window_Create@@YIXXZ=0059db30
// @ref __imp__ShowWindow@8=0079a498
// @ref __imp__SetFocus@4=0079a38c

void Mono_Window_Show_Requested()
{
    if (unknown_mono_parent_a70f04 == 0) {
        unknown_mono_requested_a70f09 = true;
        return;
    }
    if (unknown_mono_allowed_a70f08) {
        if (unknown_mono_window_a70f10 == 0) {
            Mono_Window_Create();
        }
        unknown_mono_enabled_a70f0a = true;
        ShowWindow(unknown_mono_window_a70f10, 1);
        SetFocus(unknown_mono_parent_a70f04);
    }
}
