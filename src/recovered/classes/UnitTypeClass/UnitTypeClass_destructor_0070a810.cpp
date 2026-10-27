// UnitTypeClass::~UnitTypeClass() (0x0070A810)
// Leaves UnitTypes.
#include "shared/unit_type.hpp"
// @ref ??_7UnitTypeClass@@6BIPersistStream@@@=007ae328
// @ref ??_7UnitTypeClass@@6BIRTTITypeInfo@@@=007ae30c
// @ref ??_7UnitTypeClass@@6BINoticeSink@@@=007ae304
// @ref ??_7UnitTypeClass@@6BINoticeSource@@@=007ae2fc
// @ref ?Unknown_006ECB90@@YIXPAVAbstractClass@@_N@Z=006ecb90
// @ref ?UnitTypes@@3V?$DynamicVectorClass@PAVUnitTypeClass@@@@A=00a35d48
// @ref ??1TechnoTypeClass@@UAE@XZ=006da950

UnitTypeClass::~UnitTypeClass()
{
    Unknown_006ECB90(this, true);
    UnitTypes.Delete(this);
}
