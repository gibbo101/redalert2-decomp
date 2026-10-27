// Assigns a held locomotor and transfers its COM references (0x00509830).
// Compiler COM support, reconstructed from its observed pointer operations.
#include "shared/infantry.hpp"
UnknownComPtr<ILocomotion, &unknown_uuid_ILocomotion_7ce600> &
UnknownComPtr<ILocomotion, &unknown_uuid_ILocomotion_7ce600>::operator=(ILocomotion *pointer)
{
    if (Pointer != pointer) {
        ILocomotion *previous = Pointer;
        Pointer = pointer;
        if (Pointer != 0) {
            Pointer->AddRef();
        }
        if (previous != 0) {
            previous->Release();
        }
    }
    return *this;
}
