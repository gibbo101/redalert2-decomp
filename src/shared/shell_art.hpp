// The shell/interface art unit (0x006F1810-0x006F55EF): palettes, shapes and
// panel rectangles of the main menu, loading, score and sidebar screens.
#ifndef RA2_SHARED_SHELL_ART_HPP
#define RA2_SHARED_SHELL_ART_HPP

#include "shared/rect.hpp"

// A screen-sized clipping window (0x00839640; shared/unknown_globals.hpp).
extern Rect unknown_window_839640;

// The window less the 0xA8-pixel sidebar (an inline rectangle helper: the
// sidebar layout 0x006F4C90 and draw 0x006F4620 take its width; written as a
// separate subtraction the compiler emits `add reg, -0xA8` instead of `sub`).
inline Rect Unknown_Bar_Rect()
{
    Rect rect = unknown_window_839640;
    rect.Width -= 0xA8;
    return rect;
}

#endif
