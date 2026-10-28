// void ProgressScreenClass::Init(double total, char count, HWND window) (0x0061ED80)
// Starts a progress display: the total, the player count with every
// player's progress cleared; without a window the primary surface is
// cleared instead.
#include "shared/progress_screen.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/surface.hpp"
#include "shared/dsurface.hpp"

void ProgressScreenClass::Init(double total, char count, HWND window)
{
    Total = total;
    Count = count;
    for (int index = 0; index < Count; index++) {
        Progress[index] = 0;
    }
    unknown_60 = true;
    if (window != 0) {
        Window = window;
    } else {
        unknown_surface_839954->Fill(0);
    }
    Name = 0;
    unknown_7c = -1;
}
