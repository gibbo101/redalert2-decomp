// long __stdcall AircraftClass::Is_Loaded() (0x0041AF20, IFlyControl slot 5)
// Whether +0xFC is set.
#include "shared/aircraft.hpp"

long __stdcall AircraftClass::Is_Loaded()
{
    return (bool)(Cargo.Object != 0);
}
