// void TabClass::Unknown_006A1770() (0x006A1770)
// Redraws the bar: sets +0x4F15 and restarts the +0x4F08 timer at 7 frames.
#include "shared/tab.hpp"
// @ref ?Frame@@3JA=00a40d2c

void TabClass::Unknown_006A1770()
{
    unknown_4f15 = true;
    Flag_To_Redraw(false);
    unknown_4f08 = 7;
}
