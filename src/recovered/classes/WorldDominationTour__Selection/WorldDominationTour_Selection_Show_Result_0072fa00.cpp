// void Selection::Show_Result(int faction) (0x0072FA00)
#ifndef VECTOR_IMPLEMENT_ALL
#define VECTOR_IMPLEMENT_ALL
#endif
#include "shared/wdt_selection.hpp"
namespace WorldDominationTour {
void Selection::Show_Result(int faction)
{
    Set_Description(L"", 0);
    int last = TheCampaign->Properties->Last_Conflict();
    int day = TheCampaign->Last_Day(faction);
    if (last - day > 8) {
        day = last - 8;
    }
    rc_ptr<State> state = TheCampaign->TheHistory->Get_State(day);
    if (state.Get() != 0) {
        int owned = state->Count_Owned(TheCampaign->Player_Faction());
        if (owned >= MegaWinningThreshold) {
            TheVoices.Say(0, 0, owned >= 30, true, 0);
        } else if (owned <= MegaLosingThreshold) {
            TheVoices.Say(0, 1, owned <= 0, true, 0);
        } else {
            TheVoices.Say(0, 2, true, true, 0);
        }
        Animate_Days(day, last);
        while (TheVoices.Is_Speaking() && !Escaped) {
            Run(5);
            Check_Escape();
        }
    }
}
}
// @ref ??_C@_11A@?$AA?$AA@=00839d4c
// @ref ??_7?$rc_ptr@VState@WorldDominationTour@@@@6B@=007aefe4
// @ref ??_G?$rc_ptr@VState@WorldDominationTour@@@@UAEPAXI@Z=00726b70
// @ref ?Run@MSEngine@@QAEXH@Z=005b3550
// @ref ?Say@Voices@WorldDominationTour@@QAEXHH_N0H@Z=00732510
