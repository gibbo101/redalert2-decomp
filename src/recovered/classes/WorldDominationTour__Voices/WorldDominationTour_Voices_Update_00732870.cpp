// void WorldDominationTour::Voices::Update() (0x00732870)
// Once the delay ran out and nothing is playing: drops the line just said
// and plays the next queued one.
#include "shared/wdt_voices.hpp"

namespace WorldDominationTour {

void Voices::Update()
{
    if (Timer.Value() == 0 && Queue.Count() > 0 && !Speech_Is_Playing()) {
        if (!Idle) {
            Queue.Delete(0);
            if (Pending > 0) {
                Pending--;
            }
        }
        if (Queue.Count() > 0) {
            Speech_Play(Unknown_00716640(Queue[0].Get()), -1, -1);
            Idle = false;
        } else {
            Pending = 0;
            Idle = true;
        }
    }
}

}
