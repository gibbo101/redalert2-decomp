// long __stdcall AircraftClass::Is_Fighter() (0x0041AF90, IFlyControl slot 7)
#include "shared/aircraft.hpp"

long __stdcall AircraftClass::Is_Fighter()
{
    return Type->Fighter != 0;
}
