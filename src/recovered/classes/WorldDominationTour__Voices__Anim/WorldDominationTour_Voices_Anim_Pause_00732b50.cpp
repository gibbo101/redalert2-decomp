// void Voices::Anim::Pause() (0x00732B50)
#include "shared/wdt_voices.hpp"

namespace WorldDominationTour {

void Voices::Anim::Pause()
{
    Timer.Stop();
}

}
