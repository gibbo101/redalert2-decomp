// bool WorldDominationTour::Voices::Is_Speaking() (0x00732A40)
#include "shared/wdt_voices.hpp"

namespace WorldDominationTour {

bool Voices::Is_Speaking()
{
    return Speech_Is_Playing();
}

}
