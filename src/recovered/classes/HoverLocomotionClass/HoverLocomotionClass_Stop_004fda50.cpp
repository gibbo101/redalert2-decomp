// void HoverLocomotionClass::Stop() (0x004FDA50)
#include "shared/hover_locomotion.hpp"

void HoverLocomotionClass::Stop()
{
    LinkedTo->unknown_slot260(0, 1);
    unknown_50 = 0;
    unknown_48 = 0;
    LinkedTo->unknown_slot306(0);
}
