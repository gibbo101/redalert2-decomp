// void Selection::Remove_Territory_Anims() (0x0072F180)
#ifndef VECTOR_IMPLEMENT_ALL
#define VECTOR_IMPLEMENT_ALL
#endif
#include "shared/wdt_selection.hpp"
namespace WorldDominationTour {
void Selection::Remove_Territory_Anims()
{
    for (TerritoryCursor cursor(TheMap->Territories); cursor; ++cursor) {
        MSAnim *anim = (MSAnim *)(*cursor)->Take_unknown_2c();
        if (anim != 0) {
            Remove_Anim(anim);
        }
    }
}
}
// @ref ??_7?$VectorCursor@V?$rc_ptr@VTerritory@WorldDominationTour@@@@V?$DynamicVectorClass@V?$rc_ptr@VTerritory@WorldDominationTour@@@@@@@@6B@=007af390
// @ref ??_G?$VectorCursor@V?$rc_ptr@VTerritory@WorldDominationTour@@@@V?$DynamicVectorClass@V?$rc_ptr@VTerritory@WorldDominationTour@@@@@@@@UAEPAXI@Z=007303d0
// @ref ?Valid@?$VectorCursor@V?$rc_ptr@VTerritory@WorldDominationTour@@@@V?$DynamicVectorClass@V?$rc_ptr@VTerritory@WorldDominationTour@@@@@@@@UBE_NXZ=00730390
// @ref ?Next@?$VectorCursor@V?$rc_ptr@VTerritory@WorldDominationTour@@@@V?$DynamicVectorClass@V?$rc_ptr@VTerritory@WorldDominationTour@@@@@@@@UAEAAV1@XZ=00730430
// @ref ?Prev@?$VectorCursor@V?$rc_ptr@VTerritory@WorldDominationTour@@@@V?$DynamicVectorClass@V?$rc_ptr@VTerritory@WorldDominationTour@@@@@@@@UAEAAV1@XZ=00730440
