// Wstring WorldDominationTour::CampaignProperties::unknown_10() const (0x0072D2E0)
#include "shared/world_domination_tour.hpp"

namespace WorldDominationTour {

Wstring CampaignProperties::unknown_10() const
{
    return Wstring(TheWDTState.Get() ? TheWDTState->unknown_10 : "");
}

}
