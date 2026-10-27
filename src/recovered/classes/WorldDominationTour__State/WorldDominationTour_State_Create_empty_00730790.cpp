// rc_ptr<State> __fastcall WorldDominationTour::State::Create() (0x00730790)
#include "shared/world_domination_tour.hpp"

namespace WorldDominationTour {

rc_ptr<State> __fastcall State::Create()
{
    return rc_ptr<State>(new State());
}

}
