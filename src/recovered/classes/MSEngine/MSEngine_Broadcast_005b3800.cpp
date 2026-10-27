// void MSEngine::Broadcast(int unknown1) (0x005B3800)
// Passes a value to slot 8 of every animation.
#include "shared/ms_engine.hpp"

void MSEngine::Broadcast(int unknown1)
{
    for (int index = 0; index < Anims.Count(); index++) {
        Anims[index]->Unknown_Slot8(unknown1);
    }
}
