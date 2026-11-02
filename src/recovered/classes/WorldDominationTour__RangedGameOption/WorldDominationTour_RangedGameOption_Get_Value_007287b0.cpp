// int WorldDominationTour::RangedGameOption::Get_Value(rc_ptr<WDTTerritory> const &territory) const (0x007287B0)
// 2 when the territory's value is in the middle range, else 0.
#include "shared/wdt_game_options.hpp"

namespace WorldDominationTour {

int RangedGameOption::Get_Value(rc_ptr<WDTTerritory> const &territory) const
{
    if (Get_Range(territory) == 4) {
        return 2;
    }
    return 0;
}

}
