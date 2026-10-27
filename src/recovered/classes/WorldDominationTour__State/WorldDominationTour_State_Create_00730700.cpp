// rc_ptr<State> __fastcall WorldDominationTour::State::Create(rc_ptr<WDTState> const &wdt_state, int index) (0x00730700)
#include "shared/world_domination_tour.hpp"

namespace WorldDominationTour {

rc_ptr<State> __fastcall State::Create(rc_ptr<WDTState> const &wdt_state, int index)
{
    return rc_ptr<State>(new State(wdt_state, index));
}

}
