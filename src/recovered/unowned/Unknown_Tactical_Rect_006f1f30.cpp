// Rect Unknown_006F1F30() (0x006F1F30)
// The tactical view rectangle: the screen window less the sidebar (0xA8 wide,
// at the left unless the sidebar is on the left or 0x00A40D13 is set) and the
// 0x20-pixel top bar.
// @ref ?unknown_window_839640@@3VRect@@A=00839640
// @ref ?unknown_flag_a40b30@@3_NA=00a40b30
// @ref ?unknown_flag_a40d13@@3_NA=00a40d13
#include "shared/rect.hpp"

extern Rect unknown_window_839640;
extern bool unknown_flag_a40b30;
extern bool unknown_flag_a40d13;

Rect __fastcall Unknown_006F1F30()
{
    Rect rect = unknown_window_839640;
    rect.X = 0;
    rect.Y = 0;
    if (!unknown_flag_a40b30 && !unknown_flag_a40d13) {
        rect.X = 0xA8;
    }
    rect.Width -= 0xA8;
    rect.Height -= 0x20;
    return rect;
}
