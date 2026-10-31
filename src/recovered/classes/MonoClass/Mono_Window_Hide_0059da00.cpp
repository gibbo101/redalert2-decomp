// void Mono_Window_Hide() (0x0059DA00)
#include "shared/win32_api.hpp"
#include "shared/mono_window.hpp"
// @ref ?unknown_mono_requested_a70f09@@3_NA=00a70f09
// @ref ?unknown_mono_enabled_a70f0a@@3_NA=00a70f0a
// @ref ?unknown_mono_window_a70f10@@3PAUHWND__@@A=00a70f10
// @ref __imp__ShowWindow@8=0079a498

void Mono_Window_Hide()
{
    unknown_mono_requested_a70f09 = false;
    if (unknown_mono_window_a70f10 != 0) {
        unknown_mono_enabled_a70f0a = false;
        ShowWindow(unknown_mono_window_a70f10, 0);
    }
}
