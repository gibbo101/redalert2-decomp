// bool Voices::Anim::Unknown_Slot4(Surface *surface, Rect *dirty) (0x00732BC0)
// Plays the next queued line when due; never asks the engine to delete it.
#include "shared/wdt_voices.hpp"

namespace WorldDominationTour {

bool Voices::Anim::Unknown_Slot4(Surface *surface, Rect *dirty)
{
    Owner->Update();
    return false;
}

}
