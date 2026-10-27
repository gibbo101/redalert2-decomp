// unsigned long __stdcall AircraftClass::Release() (0x00414010, slot 2)
#include "shared/aircraft.hpp"
// @ref ?Release@AbstractClass@@UAGKXZ=004100b0

unsigned long __stdcall AircraftClass::Release()
{
    return FootClass::Release();
}
