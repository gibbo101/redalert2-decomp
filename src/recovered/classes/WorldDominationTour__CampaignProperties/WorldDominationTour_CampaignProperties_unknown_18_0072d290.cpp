// int WorldDominationTour::CampaignProperties::unknown_18() const (0x0072D290)
#include "shared/world_domination_tour.hpp"

namespace WorldDominationTour {

int CampaignProperties::unknown_18() const
{
    if (TheWDTState.Get()) {
        return TheWDTState->unknown_18;
    }
    return 0;
}

}
