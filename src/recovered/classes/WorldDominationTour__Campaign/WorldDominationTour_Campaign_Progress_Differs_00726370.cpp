// bool WorldDominationTour::Campaign::Progress_Differs(int faction) const (0x00726370)
// Whether the saved CampaignID differs from the properties', or else the
// faction's saved LastDay from the properties' last conflict.
#include "shared/wdt_campaign.hpp"

namespace WorldDominationTour {

bool Campaign::Progress_Differs(int faction) const
{
    int value = Properties->unknown_18();
    if (ID != value) {
        return true;
    }
    value = Properties->Last_Conflict();
    return LastDay[faction] != value ? true : false;
}

}
