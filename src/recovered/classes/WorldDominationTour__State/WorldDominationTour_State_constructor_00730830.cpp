// WorldDominationTour::State::State(rc_ptr<WDTState> const &wdt_state, unsigned index) (0x00730830)
// Takes the owner array of conflict index of the wdt_state (none when the
// index is out of range).
#include "shared/world_domination_tour.hpp"

namespace WorldDominationTour {

State::State(rc_ptr<WDTState> const &wdt_state, unsigned index) :
    TheWDTState(wdt_state),
    Owners(0)
{
    // Through Get(): rc_ptr::operator-> (with its null test) would not fold
    // the second read (0x00730830 and its copy in Create 0x00730700).
    if (TheWDTState.Get() && index < TheWDTState.Get()->ConflictCount) {
        Owners = (unsigned char *)TheWDTState.Get()->unknown_44[index];
    }
}

}
