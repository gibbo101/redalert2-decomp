// void ProgressScreenClass::Init(double total, char count, int unknown) (0x0061ED80)
// Starts a progress display: the total, the player count with every
// player's progress cleared; without an image the primary surface is
// cleared instead.
#include "shared/progress_screen.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/surface.hpp"

void ProgressScreenClass::Init(double total, char count, int unknown)
{
    Total = total;
    Count = count;
    for (int index = 0; index < Count; index++) {
        Progress[index] = 0;
    }
    unknown_60 = true;
    if (unknown != 0) {
        unknown_64 = unknown;
    } else {
        unknown_surface_839954->Fill(0);
    }
    unknown_50 = 0;
    unknown_7c = -1;
}
