// WorldDominationTour::Voices::~Voices() (0x00731680)
#include "shared/wdt_voices.hpp"

namespace WorldDominationTour {

Voices::~Voices()
{
    Stop();
    if (Stream != 0) {
        Audio_Stream_Destroy(Stream);
    }
}

}
