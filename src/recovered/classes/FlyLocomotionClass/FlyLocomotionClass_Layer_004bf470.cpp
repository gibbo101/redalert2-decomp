// int __stdcall FlyLocomotionClass::Layer() (0x004BF470, ILocomotion 29)
// Above ground (slot 108 positive): layer 4, otherwise 2.
#include "shared/fly_locomotion.hpp"

int __stdcall FlyLocomotionClass::Layer()
{
    return LinkedTo->unknown_slot108() <= 0 ? 2 : 4;
}
