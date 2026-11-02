// rc_ptr<Campaign> const &__fastcall Previous_WDT_Campaign_00769680() (0x00769680): the campaign the
// WOL callbacks stored as the previous cycle's (TibSun WDT_Get_Resumed_Campaign).
#include "shared/reference_counted.hpp"
namespace WorldDominationTour { class Campaign; }
extern rc_ptr<WorldDominationTour::Campaign> WDT_Previous_Campaign_b2ad88;
// @ref ?WDT_Previous_Campaign_b2ad88@@3V?$rc_ptr@VCampaign@WorldDominationTour@@@@A=00b2ad88

rc_ptr<WorldDominationTour::Campaign> const &__fastcall Previous_WDT_Campaign_00769680()
{
    return WDT_Previous_Campaign_b2ad88;
}
