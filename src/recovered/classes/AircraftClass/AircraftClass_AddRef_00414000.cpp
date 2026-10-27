// unsigned long __stdcall AircraftClass::AddRef() (0x00414000, slot 1)
#include "shared/aircraft.hpp"
// @ref ?AddRef@AbstractClass@@UAGKXZ=004100a0

unsigned long __stdcall AircraftClass::AddRef()
{
    return FootClass::AddRef();
}
