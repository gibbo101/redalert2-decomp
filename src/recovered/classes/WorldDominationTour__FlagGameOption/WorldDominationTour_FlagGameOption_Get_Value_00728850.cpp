// int WorldDominationTour::FlagGameOption::Get_Value(rc_ptr<WDTTerritory> const &territory) const (0x00728850)
// OnValue when the territory's OptionFlags has Flag set, else OffValue.
#include "shared/wdt_game_options.hpp"

namespace WorldDominationTour {

int FlagGameOption::Get_Value(rc_ptr<WDTTerritory> const &territory) const
{
    if (territory->OptionFlags & Flag) {
        return OnValue;
    }
    return OffValue;
}

}
