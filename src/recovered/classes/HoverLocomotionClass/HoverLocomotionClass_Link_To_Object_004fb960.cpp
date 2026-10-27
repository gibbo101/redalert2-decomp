// HRESULT __stdcall HoverLocomotionClass::Link_To_Object(void *object) (0x004FB960, ILocomotion 3)
// Links, then turns at twice the type's rate.
#include "shared/hover_locomotion.hpp"
// @ref ?Link_To_Object@LocomotionClass@@UAGJPAX@Z=0053d010
// @ref ??0FacingClass@@QAE@H@Z=004b89f0

HRESULT __stdcall HoverLocomotionClass::Link_To_Object(void *object)
{
    HRESULT result = LocomotionClass::Link_To_Object(object);
    FacingClass facing(LinkedTo->unknown_slot32()->ROT * 2);
    unknown_30 = facing;
    return result;
}
