// BuildingClass::BuildingClass(NoInitClass const &noinit) (0x00438C20)
// The loading constructor: rebuilds the stage and the two infantry lists,
// which have no NoInitClass constructors.
#include "shared/building.hpp"
// @ref ??0TechnoClass@@QAE@ABVNoInitClass@@@Z=006c1f10
// @ref ??_7BuildingClass@@6BIPersistStream@@@=0079cbbc
// @ref ??_7BuildingClass@@6BIRTTITypeInfo@@@=0079cba0
// @ref ??_7BuildingClass@@6BINoticeSink@@@=0079cb98
// @ref ??_7BuildingClass@@6BINoticeSource@@@=0079cb90
// @ref ??_7?$DynamicVectorClass@PAVInfantryClass@@@@6B@=0079d054
// @ref ?Frame@@3HA=00a40d2c

BuildingClass::BuildingClass(NoInitClass const &noinit) :
    TechnoClass(noinit),
    unknown_420(noinit),
    unknown_448(noinit),
    unknown_4d8(noinit),
    unknown_5a0(noinit)
{
}
