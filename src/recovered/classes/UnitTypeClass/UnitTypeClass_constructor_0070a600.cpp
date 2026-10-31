// UnitTypeClass::UnitTypeClass(char const *ini_name) (0x0070A600)
#include "shared/unit_type.hpp"
// @ref ??0TechnoTypeClass@@QAE@PBDH@Z=006d9b40
// @ref ??_7UnitTypeClass@@6BIPersistStream@@@=007ae328
// @ref ??_7UnitTypeClass@@6BIRTTITypeInfo@@@=007ae30c
// @ref ??_7UnitTypeClass@@6BINoticeSink@@@=007ae304
// @ref ??_7UnitTypeClass@@6BINoticeSource@@@=007ae2fc
// @ref ?Create_ID@AbstractClass@@UAGXXZ=0040ffd0
// @ref ?UnitTypes@@3V?$DynamicVectorClass@PAVUnitTypeClass@@@@A=00a35d48

UnitTypeClass::UnitTypeClass(char const *ini_name) :
    TechnoTypeClass(ini_name, -1),
    ArrayIndex(-1),
    MovementRestrictedTo(-1),
    HalfDamageSmokeLocation(0, 0, 0),
    Passive(false),
    CrateGoodie(false),
    Harvester(false),
    Weeder(false),
    unknown_ba8(false),
    unknown_ba9(false),
    DeployToFire(false),
    IsSimpleDeployer(false),
    IsTilter(true),
    UseTurretShadow(false),
    TooBigToFitUnderBridge(false),
    CanBeach(false),
    SmallVisceroid(false),
    LargeVisceroid(false),
    CarriesCrate(false),
    NonVehicle(false),
    StandingFrames(0),
    DeathFrames(0),
    DeathFrameRate(1),
    StartStandFrame(-1),
    StartWalkFrame(-1),
    StartFiringFrame(-1),
    StartDeathFrame(-1),
    MaxDeathCounter(-1),
    Facings(8),
    AltImage(0),
    WalkFrames(12),
    FiringFrames(0)
{
    Create_ID();
    RotCount = 32;
    UnitTypes.Add(this);
    ArrayIndex = UnitTypes.ID(this);
    int index;
    for (index = 0; index < 2; index++) {
        FiringSyncFrame[index] = -1;
    }
    for (index = 0; index < 4; index++) {
        BurstDelay[index] = -1;
    }
    ImmuneToPsionics = false;
    Parasiteable = true;
    Organic = false;
    ConsideredAircraft = false;
}
