// void Selection::Hover_2(Point2D const &point) (0x0072E720)
#ifndef VECTOR_IMPLEMENT_ALL
#define VECTOR_IMPLEMENT_ALL
#endif
#include "shared/wdt_selection.hpp"
namespace WorldDominationTour {
void Selection::Hover_2(Point2D const &point)
{
    int index = TheMap->Territory_At(point);
    if (index != unknown_460) {
        unknown_460 = index;
        Select_Territory(TheMap->Get_Territory(index));
    }
}
}
// @ref ?Territory_At@Map@WorldDominationTour@@QBEHABUPoint2D@@@Z=0072a660
// @ref ?Find_Territory@WorldDominationTour@@YI?AV?$rc_ptr@VTerritory@WorldDominationTour@@@@AAV?$DynamicVectorClass@V?$rc_ptr@VTerritory@WorldDominationTour@@@@@@H@Z=007311b0
// @ref ?Select_Territory@Selection@WorldDominationTour@@QAE_NABV?$rc_ptr@VTerritory@WorldDominationTour@@@@@Z=0072ed80
