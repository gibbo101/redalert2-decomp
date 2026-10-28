// RadBeam *RadBeam::Allocate(int type) (0x00635440)
// A new beam of the type, listed; type 1 steps every 10 leptons, the others
// every 20.
#include "shared/rad_beam_list.hpp"

RadBeam *__fastcall RadBeam::Allocate(int type)
{
    RadBeam *beam = new RadBeam(type);
    RadBeamList::Array.Add(beam);
    beam->Set_Step_Length(type == 1 ? 10 : 20);
    return beam;
}
