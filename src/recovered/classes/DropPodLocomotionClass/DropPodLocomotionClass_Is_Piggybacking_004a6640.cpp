// bool __stdcall DropPodLocomotionClass::Is_Piggybacking() (0x004A6640, IPiggyback 7)
#include "shared/droppod_locomotion.hpp"

bool __stdcall DropPodLocomotionClass::Is_Piggybacking()
{
    return Piggybacker != 0;
}
