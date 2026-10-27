// static int __fastcall AircraftTypeClass::From_Name(char const *name) (0x0041BE60)
// Index of the type with this ID (case-insensitive), or -1.
#include "shared/aircraft_type.hpp"
// @ref ?AircraftTypes@@3V?$DynamicVectorClass@PAVAircraftTypeClass@@@@A=00a3d278
// @ref __stricmp=00781f20

int __fastcall AircraftTypeClass::From_Name(char const *name)
{
    if (name) {
        for (int index = 0; index < AircraftTypes.Count(); index++) {
            if (_stricmp(AircraftTypes[index]->ID, name) == 0) {
                return index;
            }
        }
    }
    return -1;
}
