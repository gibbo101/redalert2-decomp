// void Selection::Show_Progress(int faction) (0x0072F5A0)
#ifndef VECTOR_IMPLEMENT_ALL
#define VECTOR_IMPLEMENT_ALL
#endif
#include "shared/wdt_selection.hpp"
namespace WorldDominationTour {
void Selection::Show_Progress(int faction)
{
    Set_Description(0, 0);
    int last = TheCampaign->Properties->Last_Conflict();
    bool won = true;
    int day = TheCampaign->Last_Day(faction);
    if (last - day > 8) {
        day = last - 8;
    }
    if (day != last) {
        won = !Show_Days(day, last);
    } else {
        bool mega = false;
        int result = Get_Result(last, mega);
        TheVoices.Say(2, result, mega, true, 0);
    }
    Set_Description(0, 0);
    Check_Escape();
    Show_State(TheCampaign->TheHistory->Get_State(last), true, won);
    TheCampaign->Save_Progress(faction);
}
}
// @ref ?Say@Voices@WorldDominationTour@@QAEXHH_N0H@Z=00732510
// @ref ?Show_State@Selection@WorldDominationTour@@QAEXABV?$rc_ptr@VState@WorldDominationTour@@@@_N1@Z=0072e780
