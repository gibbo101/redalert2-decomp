// int WorldDominationTour::Territory::Take_unknown_2c() (0x007311A0): returns and clears +0x2C.
#include "shared/world_domination_tour.hpp"

namespace WorldDominationTour {

int Territory::Take_unknown_2c()
{
    int value = unknown_2c;
    unknown_2c = 0;
    return value;
}

}
