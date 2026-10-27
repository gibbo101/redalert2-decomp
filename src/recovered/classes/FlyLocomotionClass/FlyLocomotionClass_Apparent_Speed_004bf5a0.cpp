// int __stdcall FlyLocomotionClass::Apparent_Speed() (0x004BF5A0, ILocomotion 33)
// The type's speed scaled by the current speed fraction.
#include "shared/fly_locomotion.hpp"
// @ref __ftol=0077f110

int __stdcall FlyLocomotionClass::Apparent_Speed()
{
    return LinkedTo->unknown_slot32()->Speed * unknown_48;
}
