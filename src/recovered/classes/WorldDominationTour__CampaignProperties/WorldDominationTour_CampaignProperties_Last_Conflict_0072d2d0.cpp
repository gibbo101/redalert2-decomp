// int WorldDominationTour::CampaignProperties::Last_Conflict() const (0x0072D2D0)
#include "shared/world_domination_tour.hpp"

namespace WorldDominationTour {

int CampaignProperties::Last_Conflict() const
{
    if (TheWDTState.Get()) {
        return TheWDTState->ConflictCount - 1;
    }
    return 0;
}

}
