// int WorldDominationTour::State::Count_Owned(int owner) const (0x00730900)
// How many territories the state gives owner (2 for the byte 1, 3 for the
// byte 2; other owners count nothing).
#include "shared/world_domination_tour.hpp"

namespace WorldDominationTour {

int State::Count_Owned(int owner) const
{
    if (TheWDTState.Get() != 0 && Owners != 0) {
        int count = 0;
        unsigned char const *owners = Owners;
        unsigned i = TheWDTState->unknown_20;
        while (i--) {
            switch (*owners++) {
                case 1:
                    if (owner == 2) {
                        count++;
                    }
                    break;
                case 2:
                    if (owner == 3) {
                        count++;
                    }
                    break;
            }
        }
        return count;
    }
    return 0;
}

}
