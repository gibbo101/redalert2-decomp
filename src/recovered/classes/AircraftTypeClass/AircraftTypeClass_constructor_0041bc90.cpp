// AircraftTypeClass::AircraftTypeClass(char const *ini_name) (0x0041BC90)
// Speed type 4; joins AircraftTypes and records its index; aircraft
// defaults for inherited flags.
#include "shared/aircraft_type.hpp"
// @ref ??0TechnoTypeClass@@QAE@PBDH@Z=006d9b40
// @ref ??_7AircraftTypeClass@@6BIPersistStream@@@=0079b678
// @ref ??_7AircraftTypeClass@@6BIRTTITypeInfo@@@=0079b65c
// @ref ??_7AircraftTypeClass@@6BINoticeSink@@@=0079b654
// @ref ??_7AircraftTypeClass@@6BINoticeSource@@@=0079b64c
// @ref ?Create_ID@AbstractClass@@UAGXXZ=0040ffd0
// @ref ?AircraftTypes@@3V?$DynamicVectorClass@PAVAircraftTypeClass@@@@A=00a3d278

AircraftTypeClass::AircraftTypeClass(char const *ini_name) :
    TechnoTypeClass(ini_name, 4),
    ArrayIndex(-1),
    Carryall(false),
    Rotors(false),
    CustomRotor(false),
    Landable(false),
    AirportBound(false),
    Fighter(false)
{
    Create_ID();
    AircraftTypes.Add(this);
    ArrayIndex = AircraftTypes.ID(this);
    Parasiteable = true;
    ConsideredAircraft = true;
    MoveToShroud = false;
    RotCount = 32;
    Trailer = 0;
    SpawnDelay = 3;
    ImmuneToPsionics = false;
    Organic = false;
}
