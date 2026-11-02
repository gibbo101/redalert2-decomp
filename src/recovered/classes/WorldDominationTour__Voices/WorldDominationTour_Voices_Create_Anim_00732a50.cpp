// WorldDominationTour::Voices::Anim *WorldDominationTour::Voices::Create_Anim() (0x00732A50)
// A new animation that plays this object's queue.
#include "shared/wdt_voices.hpp"

namespace WorldDominationTour {

Voices::Anim *Voices::Create_Anim()
{
    return new Anim(this);
}

}
