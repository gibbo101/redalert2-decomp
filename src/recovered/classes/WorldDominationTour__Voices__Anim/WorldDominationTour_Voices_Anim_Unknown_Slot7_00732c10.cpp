// bool Voices::Anim::Unknown_Slot7() (0x00732C10)
// True once nothing is being said.
#include "shared/wdt_voices.hpp"

namespace WorldDominationTour {

bool Voices::Anim::Unknown_Slot7()
{
    return !Speech_Is_Playing();
}

}
