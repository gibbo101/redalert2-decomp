// ProgressBarClass::ProgressBarClass (0x0042B970), Westwood's BAR.CPP.
#include "shared/progress_bar.hpp"
#include "shared/gadget.hpp"
#include "shared/mouse.hpp"
#include "shared/surface.hpp"
#include "shared/unknown_globals.hpp"

ProgressBarClass::ProgressBarClass(int x, int y, int width, int height, int forecolor, int backcolor,
                                   int bordercolor) :
    X(x),
    Y(y),
    Width(width),
    Height(height),
    BarColor(forecolor),
    BackColor(backcolor),
    BorderColor(bordercolor),
    CurrentValue(0),
    LastDisplayCurrent(0),
    IsDrawn(false)
{
}
