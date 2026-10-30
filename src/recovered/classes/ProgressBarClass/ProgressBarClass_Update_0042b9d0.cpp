// ProgressBarClass::Update (0x0042B9D0): redraws when the value moved by a tenth or more.
#include "shared/progress_bar.hpp"
#include "shared/gadget.hpp"
#include "shared/mouse.hpp"
#include "shared/surface.hpp"
#include "shared/unknown_globals.hpp"

bool ProgressBarClass::Update(double value)
{
    CurrentValue = value;
    if (!IsDrawn || value - LastDisplayCurrent >= 0.1) {
        Redraw();
        return true;
    }
    return false;
}
