// ConflictCursor WorldDominationTour::Campaign::Find_Conflict(int index) (0x00726730)
// A cursor on the first conflict whose territory index matches.
#include "shared/wdt_campaign.hpp"
// @ref ??_E?$VectorCursor@V?$rc_ptr@VConflict@WorldDominationTour@@@@V?$DynamicVectorClass@V?$rc_ptr@VConflict@WorldDominationTour@@@@@@@@UAEPAXI@Z=00726b20
// @ref ?Valid@?$VectorCursor@V?$rc_ptr@VConflict@WorldDominationTour@@@@V?$DynamicVectorClass@V?$rc_ptr@VConflict@WorldDominationTour@@@@@@@@UBE_NXZ=00726ab0
// @ref ?Next@?$VectorCursor@V?$rc_ptr@VConflict@WorldDominationTour@@@@V?$DynamicVectorClass@V?$rc_ptr@VConflict@WorldDominationTour@@@@@@@@UAEAAV1@XZ=00726ef0
// @ref ?Prev@?$VectorCursor@V?$rc_ptr@VConflict@WorldDominationTour@@@@V?$DynamicVectorClass@V?$rc_ptr@VConflict@WorldDominationTour@@@@@@@@UAEAAV1@XZ=00726f00
// @ref ??_7?$VectorCursor@V?$rc_ptr@VConflict@WorldDominationTour@@@@V?$DynamicVectorClass@V?$rc_ptr@VConflict@WorldDominationTour@@@@@@@@6B@=007af054

namespace WorldDominationTour {

ConflictCursor Campaign::Find_Conflict(int index)
{
    ConflictCursor cursor(Conflicts);
    while (cursor && (*cursor)->unknown_7273f0() != index) {
        ++cursor;
    }
    return cursor;
}

}
