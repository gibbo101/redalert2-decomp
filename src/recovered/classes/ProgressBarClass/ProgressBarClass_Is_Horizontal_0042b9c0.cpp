// ProgressBarClass::Is_Horizontal (0x0042B9C0): the bar fills along its longer side.
#include "shared/progress_bar.hpp"
#include "shared/gadget.hpp"
#include "shared/mouse.hpp"
#include "shared/surface.hpp"
#include "shared/unknown_globals.hpp"

bool ProgressBarClass::Is_Horizontal() const
{
    if (Width > Height) return true;
    return false;
}
