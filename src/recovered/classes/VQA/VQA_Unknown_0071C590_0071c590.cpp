// bool VQA_Unknown_0071C590() (0x0071C590)
// Handles one pending window message (counted in 0x00A52298); false when
// the message loop has to end (WM_QUIT).
#include "shared/movie.hpp"
// @ref ?unknown_message_count_a52298@@3HA=00a52298
// @ref ?unknown_peek_message_522ed0@@YIHPAUtagMSG@@PAUHWND__@@III@Z=00522ed0
// @ref ?unknown_get_message_522e90@@YIHPAUtagMSG@@PAUHWND__@@II@Z=00522e90
// @ref __imp__TranslateMessage@4=0079a4b0
// @ref __imp__DispatchMessageA@4=0079a4b4

bool VQA_Unknown_0071C590()
{
    MSG message;
    ++unknown_message_count_a52298;
    if (unknown_peek_message_522ed0(&message, 0, 0, 0, 0)) {
        if (unknown_get_message_522e90(&message, 0, 0, 0)) {
            TranslateMessage(&message);
            DispatchMessageA(&message);
        } else {
            return false;
        }
    }
    return true;
}
