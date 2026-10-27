// bool WorldDominationTour::GameOption::Is_Forced(rc_ptr<WDTTerritory> const &territory) const (0x00728680)
// Never forced here (ValueGameOption::Get_Value returns 2 when it is).
#include "shared/wdt_game_options.hpp"

namespace WorldDominationTour {

bool GameOption::Is_Forced(rc_ptr<WDTTerritory> const &territory) const
{
    return false;
}

}
