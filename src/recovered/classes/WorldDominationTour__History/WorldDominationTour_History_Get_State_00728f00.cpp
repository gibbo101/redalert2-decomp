// rc_ptr<State> WorldDominationTour::History::Get_State(int index) const (0x00728F00)
// The state of entry index of the wdt_state (State::Create).
#include "shared/world_domination_tour.hpp"

namespace WorldDominationTour {

rc_ptr<State> History::Get_State(int index) const
{
    return State::Create(TheWDTState, index);
}

}
