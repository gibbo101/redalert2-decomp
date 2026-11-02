// int WorldDominationTour::State::Owner_Of(unsigned territory) const (0x00730890)
// The owner the state records for a territory: 1-3 for the bytes 0-2, 0 for
// anything else, an index out of range or a state without data.
#include "shared/world_domination_tour.hpp"

namespace WorldDominationTour {

int State::Owner_Of(unsigned territory) const
{
    if (TheWDTState.Get() != 0 && Owners != 0 && territory < TheWDTState->unknown_20) {
        switch (Owners[territory]) {
            case 0:
                return 1;
            case 1:
                return 2;
            case 2:
                return 3;
        }
    }
    return 0;
}

}
