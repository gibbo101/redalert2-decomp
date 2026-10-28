// Point2D __stdcall LocomotionClass::Shadow_Point() (0x0053D1C0, ILocomotion 12)
// The shadow is drawn the object's height (in pixels) lower.
#include "shared/locomotion.hpp"

Point2D __stdcall LocomotionClass::Shadow_Point()
{
    return Point2D(0, Unknown_006A2970(LinkedTo->unknown_slot108()));
}
