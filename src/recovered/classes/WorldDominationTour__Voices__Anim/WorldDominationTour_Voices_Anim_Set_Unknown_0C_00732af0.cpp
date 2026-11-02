// void Voices::Anim::Set_Unknown_0C(bool value) (0x00732AF0)
// Clearing the flag stops the voices.
#include "shared/wdt_voices.hpp"

namespace WorldDominationTour {

void Voices::Anim::Set_Unknown_0C(bool value)
{
    unknown_0C = value;
    if (!value) {
        Owner->Stop();
    }
}

}
