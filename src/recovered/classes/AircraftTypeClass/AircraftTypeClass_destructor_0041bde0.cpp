// AircraftTypeClass::~AircraftTypeClass() (0x0041BDE0)
// Leaves AircraftTypes.
#include "shared/aircraft_type.hpp"
// @ref ??_7AircraftTypeClass@@6BIPersistStream@@@=0079b678
// @ref ??_7AircraftTypeClass@@6BIRTTITypeInfo@@@=0079b65c
// @ref ??_7AircraftTypeClass@@6BINoticeSink@@@=0079b654
// @ref ??_7AircraftTypeClass@@6BINoticeSource@@@=0079b64c
// @ref ?Unknown_006ECB90@@YIXPAVAbstractClass@@_N@Z=006ecb90
// @ref ?AircraftTypes@@3V?$DynamicVectorClass@PAVAircraftTypeClass@@@@A=00a3d278
// @ref ??1TechnoTypeClass@@UAE@XZ=006da950

AircraftTypeClass::~AircraftTypeClass()
{
    Unknown_006ECB90(this, true);
    AircraftTypes.Delete(this);
}
