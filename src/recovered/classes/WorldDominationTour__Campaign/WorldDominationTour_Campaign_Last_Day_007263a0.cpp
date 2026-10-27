// int WorldDominationTour::Campaign::Last_Day(int faction) const (0x007263A0)
#include "shared/wdt_campaign.hpp"

namespace WorldDominationTour {

int Campaign::Last_Day(int faction) const
{
    return LastDay[faction];
}

}
