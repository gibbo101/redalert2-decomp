// bool __stdcall DropPodLocomotionClass::Is_Ok_To_End() (0x004A63C0, IPiggyback 5)
// Once landed while carrying a locomotor.
#include "shared/droppod_locomotion.hpp"

bool __stdcall DropPodLocomotionClass::Is_Ok_To_End()
{
    if (!Is_Moving() && Piggybacker != 0) {
        return true;
    }
    return false;
}
