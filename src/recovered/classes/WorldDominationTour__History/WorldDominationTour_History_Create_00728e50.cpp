// rc_ptr<History> __fastcall WorldDominationTour::History::Create(rc_ptr<WDTState> const &wdt_state) (0x00728E50)
// A new history of the wdt_state, returned counted.
#include "shared/world_domination_tour.hpp"

namespace WorldDominationTour {

rc_ptr<History> __fastcall History::Create(rc_ptr<WDTState> const &wdt_state)
{
    return rc_ptr<History>(new History(wdt_state));
}

}
