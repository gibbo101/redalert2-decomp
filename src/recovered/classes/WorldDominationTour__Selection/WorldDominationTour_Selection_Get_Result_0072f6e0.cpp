// int Selection::Get_Result(int index, bool &mega) (0x0072F6E0)
#ifndef VECTOR_IMPLEMENT_ALL
#define VECTOR_IMPLEMENT_ALL
#endif
#include "shared/wdt_selection.hpp"
namespace WorldDominationTour {
int Selection::Get_Result(int index, bool &mega)
{
    rc_ptr<State> state = TheCampaign->TheHistory->Get_State(index);
    if (state.Get() != 0) {
        int owned = state->Count_Owned(TheCampaign->PlayerFaction);
        if (owned <= LosingThreshold) {
            mega = owned <= MegaLosingThreshold;
            return 1;
        }
        if (owned >= WinningThreshold) {
            mega = owned >= MegaWinningThreshold;
            return 0;
        }
    }
    mega = false;
    return 2;
}
}
// @ref ?Count_Owned@State@WorldDominationTour@@QBEHH@Z=00730900
// @ref ??_7?$rc_ptr@VState@WorldDominationTour@@@@6B@=007aefe4
// @ref ??_G?$rc_ptr@VState@WorldDominationTour@@@@UAEPAXI@Z=00726b70
