// int WorldDominationTour::RangedGameOption::In_Range_Of(unsigned value) const (0x00728770)
// TibSun shape: the range value falls into (4 is the middle).
#include "shared/wdt_game_options.hpp"

namespace WorldDominationTour {

int RangedGameOption::In_Range_Of(unsigned value) const
{
    if (value <= Range0) {
        return 0;
    }
    if (value <= Range1) {
        return 1;
    }
    if (value >= Range3) {
        return 3;
    }
    if (value >= Range2) {
        return 2;
    }
    return 4;
}

}
