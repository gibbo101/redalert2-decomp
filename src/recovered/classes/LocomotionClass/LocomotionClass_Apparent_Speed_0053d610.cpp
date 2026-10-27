// int __stdcall LocomotionClass::Apparent_Speed() (0x0053D610, ILocomotion)
// The linked object's speed (FootClass slot 303).
#include "shared/locomotion.hpp"

int __stdcall LocomotionClass::Apparent_Speed()
{
    return LinkedTo->unknown_slot303();
}
