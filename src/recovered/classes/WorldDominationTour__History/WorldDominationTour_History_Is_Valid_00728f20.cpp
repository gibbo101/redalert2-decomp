// int WorldDominationTour::History::Is_Valid(unsigned index) const (0x00728F20)
// Whether index names one of the wdt_state's conflicts.
#include "shared/world_domination_tour.hpp"

namespace WorldDominationTour {

int History::Is_Valid(unsigned index) const
{
    if (TheWDTState.Get() && index < TheWDTState->ConflictCount) {
        return true;
    }
    return false;
}

}
