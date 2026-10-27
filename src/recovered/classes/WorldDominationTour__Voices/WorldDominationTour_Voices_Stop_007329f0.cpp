// void WorldDominationTour::Voices::Stop() (0x007329F0)
#include "shared/wdt_voices.hpp"

namespace WorldDominationTour {

void Voices::Stop()
{
    if (Queue.Count() > 0) {
        Speech_Stop(true);
        Queue.Clear();
    }
    Timer = CDTimerClass<SystemTimerClass>(0);
}

}
