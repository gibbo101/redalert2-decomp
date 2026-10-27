// int WorldDominationTour::CampaignProperties::unknown_14() const (0x0072D2B0)
#include "shared/world_domination_tour.hpp"

namespace WorldDominationTour {

int CampaignProperties::unknown_14() const
{
    if (TheWDTState.Get()) {
        return TheWDTState->unknown_14;
    }
    return 1;
}

}
