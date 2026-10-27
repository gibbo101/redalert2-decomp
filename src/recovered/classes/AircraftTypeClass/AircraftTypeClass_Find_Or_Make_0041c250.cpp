// static AircraftTypeClass *__fastcall AircraftTypeClass::Find_Or_Make(char const *name) (0x0041C250)
// The type with this ID, a new one when unknown, 0 for "<none>"/"none".
#include "shared/aircraft_type.hpp"
// @ref ??_C@_06CPHF@?$DMnone?$DO?$AA@=007cdecc
// @ref __stricmp=00781f20
// @ref ??_C@_04KIKH@none?$AA@=007ce0ec
// @ref ?AircraftTypes@@3V?$DynamicVectorClass@PAVAircraftTypeClass@@@@A=00a3d278
// @ref ??2@YAPAXI@Z=00782017
// @ref ??0AircraftTypeClass@@QAE@PBD@Z=0041bc90

AircraftTypeClass *__fastcall AircraftTypeClass::Find_Or_Make(char const *name)
{
    if (_stricmp("<none>", name) == 0 || _stricmp("none", name) == 0) {
        return 0;
    }
    for (int index = 0; index < AircraftTypes.Count(); index++) {
        if (_stricmp(AircraftTypes[index]->ID, name) == 0) {
            return AircraftTypes[index];
        }
    }
    return new AircraftTypeClass(name);
}
