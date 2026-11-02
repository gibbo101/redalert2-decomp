// rc_ptr<WDTTerritory> __fastcall Get_WDT_Territory_00769690(int index) (0x00769690): the territory of
// the current campaign's conflict index, or an empty pointer (TibSun WDT_Get_Territory).
#include "shared/wdt_campaign_layout.hpp"
#include "shared/world_domination_tour.hpp"
// @ref ??_7?$rc_ptr@VWDTTerritory@@@@6B@=007a452c
// @ref ??_G?$rc_ptr@VWDTTerritory@@@@UAEPAXI@Z=0051e600
// @ref ??_E?$rc_ptr@VWDTTerritory@@@@UAEPAXI@Z=0051e600
// @ref ?Find_Conflict@Campaign@WorldDominationTour@@=00726730

using namespace WorldDominationTour;

rc_ptr<Campaign> const &__fastcall Current_WDT_Campaign_00769670();

rc_ptr<WDTTerritory> __fastcall Get_WDT_Territory_00769690(int index)
{
    ConflictCursor cursor = Current_WDT_Campaign_00769670()->Find_Conflict(index);
    return cursor ? (*cursor)->Territory : rc_ptr<WDTTerritory>();
}
