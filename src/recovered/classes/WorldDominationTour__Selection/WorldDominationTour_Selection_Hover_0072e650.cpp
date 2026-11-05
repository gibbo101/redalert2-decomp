// bool Selection::Hover(Point2D const &point) (0x0072E650): refreshes the hovered territory, then selects it.
// DEAD CONSTRUCT, owner ruling: `true ?` accounts for bytes in the target (the zeroed temporary-construction
// flag at entry and the copy into territory through the out-of-line default ctor plus Set). The real source's
// condition is unknown; a plain initialisation gives 39.22.
#ifndef VECTOR_IMPLEMENT_ALL
#define VECTOR_IMPLEMENT_ALL
#endif
#include "shared/wdt_selection.hpp"
namespace WorldDominationTour {
bool Selection::Hover(Point2D const &point)
{
    Hover_2(point);
    rc_ptr<Territory> territory = true ? TheMap->Get_Territory(unknown_460) : rc_ptr<Territory>();
    return Select_Territory(territory);
}
}
