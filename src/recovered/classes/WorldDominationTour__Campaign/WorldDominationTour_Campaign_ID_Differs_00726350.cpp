// bool WorldDominationTour::Campaign::ID_Differs() const (0x00726350)
// Whether the saved CampaignID differs from the properties' (unknown_18).
#include "shared/wdt_campaign.hpp"

namespace WorldDominationTour {

bool Campaign::ID_Differs() const
{
    int value = Properties->unknown_18();
    return ID != value;
}

}
