// WorldDominationTour::State::State(rc_ptr<WDTState> const &wdt_state, unsigned index) (0x00730830)
// Takes the owner array of conflict index of the wdt_state (none when the
// index is out of range).
#include "shared/world_domination_tour.hpp"

namespace WorldDominationTour {

State::State(rc_ptr<WDTState> const &wdt_state, unsigned index) :
    TheWDTState(wdt_state),
    Owners(0)
{
    if (TheWDTState.Get() && index < TheWDTState->ConflictCount) {
        Owners = (unsigned char *)TheWDTState->unknown_44[index];
    }
}

}
