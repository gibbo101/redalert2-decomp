// void WorldDominationTour::Voices::Trim() (0x00732960)
// Drops the queued lines past the Pending ones.
#include "shared/wdt_voices.hpp"

namespace WorldDominationTour {

void Voices::Trim()
{
    int index = Queue.Count();
    while (index-- > Pending) {
        Queue.Delete(index);
    }
    if (Pending == 0) {
        Idle = true;
    }
}

}
