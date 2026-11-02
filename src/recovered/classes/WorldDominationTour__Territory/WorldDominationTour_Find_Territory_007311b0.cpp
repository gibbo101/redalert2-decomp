// rc_ptr<Territory> WorldDominationTour::Find_Territory(DynamicVectorClass<rc_ptr<Territory> > &territories, int index) (0x007311B0)
// Walks a cursor over territories to the first one whose Index is index;
// an empty pointer when none is. The unit's first source turns on the inline
// vector accessors.
#include "shared/wdt_map.hpp"
#include "shared/vector_cursor.hpp"

namespace WorldDominationTour {

rc_ptr<Territory> __fastcall Find_Territory(DynamicVectorClass<rc_ptr<Territory> > &territories, int index)
{
    VectorCursor<rc_ptr<Territory>, DynamicVectorClass<rc_ptr<Territory> > > cursor(territories);
    while (cursor && (*cursor)->Index != index) {
        ++cursor;
    }
    return cursor ? *cursor : rc_ptr<Territory>();
}

}
// @ref ??_7?$VectorCursor@V?$rc_ptr@VTerritory@WorldDominationTour@@@@V?$DynamicVectorClass@V?$rc_ptr@VTerritory@WorldDominationTour@@@@@@@@6B@=007af390
// @ref ??_G?$VectorCursor@V?$rc_ptr@VTerritory@WorldDominationTour@@@@V?$DynamicVectorClass@V?$rc_ptr@VTerritory@WorldDominationTour@@@@@@@@UAEPAXI@Z=007303d0
// @ref ?Valid@?$VectorCursor@V?$rc_ptr@VTerritory@WorldDominationTour@@@@V?$DynamicVectorClass@V?$rc_ptr@VTerritory@WorldDominationTour@@@@@@@@UBE_NXZ=00730390
// @ref ?Next@?$VectorCursor@V?$rc_ptr@VTerritory@WorldDominationTour@@@@V?$DynamicVectorClass@V?$rc_ptr@VTerritory@WorldDominationTour@@@@@@@@UAEAAV1@XZ=00730430
// @ref ?Prev@?$VectorCursor@V?$rc_ptr@VTerritory@WorldDominationTour@@@@V?$DynamicVectorClass@V?$rc_ptr@VTerritory@WorldDominationTour@@@@@@@@UAEAAV1@XZ=00730440
