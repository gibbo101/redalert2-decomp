// void UnknownComPtr<ILocomotion>::Release_Held() (0x004CDF80)
// Releases the held locomotor interface (the _com_ptr_t release step the
// units' Load and Save call out of line).
#include "shared/foot.hpp"

template <>
void UnknownComPtr<ILocomotion, &unknown_uuid_ILocomotion_7ce600>::Release_Held()
{
    if (Pointer != 0) {
        Pointer->Release();
    }
}
