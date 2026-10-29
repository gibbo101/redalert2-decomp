// WorldDominationTour::CampaignProperties::CampaignProperties(rc_ptr<WDTState> const &wdt_state) (0x0072D1F0)
// The short and long descriptions are the WDTState labels, or the (quoted) WDT:Default... labels without a state.
// @ref ??_C@_0BN@OINK@?$CCWDT?3DefaultLongDescription?$CC?$AA@=007fc280
// @ref ??_C@_0BO@CPLG@?$CCWDT?3DefaultShortDescription?$CC?$AA@=007fc2a0
// @ref ??_C@_0BE@ENJO@D?3?2Ra2?2WDTProps?4cpp?$AA@=007fc2c0
#include "shared/world_domination_tour.hpp"
#include "shared/string_table.hpp"
namespace WorldDominationTour {
CampaignProperties::CampaignProperties(rc_ptr<WDTState> const &wdt_state) :
    TheWDTState(wdt_state),
    ShortDescription(wdt_state.Get() ? StringTable::Load_String(wdt_state->ShortLabel, 0, "D:\\Ra2\\WDTProps.cpp", 20) : StringTable::Load_String("\"WDT:DefaultShortDescription\"", 0, "D:\\Ra2\\WDTProps.cpp", 20)),
    LongDescription(wdt_state.Get() ? StringTable::Load_String(wdt_state->LongLabel, 0, "D:\\Ra2\\WDTProps.cpp", 21) : StringTable::Load_String("\"WDT:DefaultLongDescription\"", 0, "D:\\Ra2\\WDTProps.cpp", 21))
{
}
}
