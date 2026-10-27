// HRESULT __stdcall LocomotionClass::Link_To_Object(void *object) (0x0053D010, ILocomotion 3)
// The object becomes both the owner and the linked object.
#include "shared/locomotion.hpp"

HRESULT __stdcall LocomotionClass::Link_To_Object(void *object)
{
    LinkedTo = (FootClass *)object;
    Owner = (FootClass *)object;
    return S_OK;
}
