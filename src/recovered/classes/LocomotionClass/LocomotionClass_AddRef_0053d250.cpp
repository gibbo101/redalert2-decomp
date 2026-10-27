// unsigned long __stdcall LocomotionClass::AddRef() (0x0053D250)
// Counts a live COM object and a reference.
#include "shared/locomotion.hpp"
// @ref ?unknown_com_objects_a6eb14@@3JA=00a6eb14
// @ref __imp__InterlockedIncrement@4=0079a1bc

unsigned long __stdcall LocomotionClass::AddRef()
{
    unknown_com_objects_a6eb14++;
    return InterlockedIncrement(&RefCount);
}
