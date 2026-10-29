// bool Selection::Show_Days(int from, int to) (0x0072FB60)
#ifndef VECTOR_IMPLEMENT_ALL
#define VECTOR_IMPLEMENT_ALL
#endif
#include "shared/wdt_selection.hpp"
namespace WorldDominationTour {
bool Selection::Show_Days(int from, int to)
{
    rc_ptr<State> before = TheCampaign->TheHistory->Get_State(from);
    int old_count = before->Count_Owned(TheCampaign->Player_Faction());
    rc_ptr<State> after = TheCampaign->TheHistory->Get_State(to);
    int new_count = after->Count_Owned(TheCampaign->Player_Faction());
    int change = new_count - old_count;
    int kind;
    bool mega;
    if (change < -1) {
        kind = 1;
        mega = change < -3 || new_count <= MegaLosingThreshold;
    } else if (change > 1) {
        kind = 0;
        mega = change > 3 || new_count >= MegaWinningThreshold;
    } else {
        kind = 2;
        mega = false;
        mega = Get_Result(to, mega) == 1 && mega;
    }
    TheVoices.Say(1, kind, mega, true, 0);
    return !Animate_Days(from, to);
}
}
// @ref ??_7?$rc_ptr@VState@WorldDominationTour@@@@6B@=007aefe4
// @ref ??_G?$rc_ptr@VState@WorldDominationTour@@@@UAEPAXI@Z=00726b70
// @ref ?Count_Owned@State@WorldDominationTour@@QBEHH@Z=00730900
// @ref ?Say@Voices@WorldDominationTour@@QAEXHH_N0H@Z=00732510
