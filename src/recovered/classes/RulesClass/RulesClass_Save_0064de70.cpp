// RulesClass::Save (0x0064DE70)
// @ref ?Save@?$TypeList@PAVAircraftTypeClass@@@@QAEXPAUIStream@@@Z=00652e40
// @ref ?Save@?$TypeList@PAVBuildingTypeClass@@@@QAEXPAUIStream@@@Z=00652a20
// @ref ?Save@?$TypeList@PAVInfantryTypeClass@@@@QAEXPAUIStream@@@Z=00652ec0
// @ref ?Save@?$TypeList@PAVSmudgeTypeClass@@@@QAEXPAUIStream@@@Z=00652c80
// @ref ?Save@?$TypeList@PAVTerrainTypeClass@@@@QAEXPAUIStream@@@Z=00652f40
// @ref ?Save@?$TypeList@PAVUnitTypeClass@@@@QAEXPAUIStream@@@Z=00652df0
// @ref ?Save@?$TypeList@PAVVoxelAnimTypeClass@@@@QAEXPAUIStream@@@Z=00652aa0
// Writes the object, then the elements of each list.
#include "shared/ccini_class.hpp"
#include "shared/rules.hpp"

void RulesClass::Save(IStream *stream)
{
    stream->Write(this, sizeof(*this), 0);
    AIIonCannonConYardValue.Save(stream);
    AIIonCannonWarFactoryValue.Save(stream);
    AIIonCannonPowerValue.Save(stream);
    AIIonCannonEngineerValue.Save(stream);
    AIIonCannonThiefValue.Save(stream);
    AIIonCannonHarvesterValue.Save(stream);
    AIIonCannonMCVValue.Save(stream);
    AIIonCannonAPCValue.Save(stream);
    AIIonCannonBaseDefenseValue.Save(stream);
    AIIonCannonPlugValue.Save(stream);
    AIIonCannonHelipadValue.Save(stream);
    AIIonCannonTempleValue.Save(stream);
    FillEarliestTeamProbability.Save(stream);
    TeamDelays.Save(stream);
    AlliedBaseDefenseCounts.Save(stream);
    SovietBaseDefenseCounts.Save(stream);
    DisabledDisguiseDetectionPercent.Save(stream);
    AIAutoDeployFrameDelay.Save(stream);
    AIPickWallDefensePercent.Save(stream);
    MinimumAIDefensiveTeams.Save(stream);
    MaximumAIDefensiveTeams.Save(stream);
    MultiplayerAICM.Save(stream);
    AIVirtualPurifiers.Save(stream);
    TotalAITeamCap.Save(stream);
    AIHateDelays.Save(stream);
    RadarEventSuppressionDistances.Save(stream);
    RadarEventVisibilityDurations.Save(stream);
    RadarEventDurations.Save(stream);
    BarrelDebris.Save(stream);
    ExplosiveVoxelDebris.Save(stream);
    PrerequisitePower.Save(stream);
    PrerequisiteFactory.Save(stream);
    PrerequisiteBarracks.Save(stream);
    PrerequisiteRadar.Save(stream);
    PrerequisiteTech.Save(stream);
    PrerequisiteProc.Save(stream);
    CreditTicks.Save(stream);
    LightningSounds.Save(stream);
    Scorches.Save(stream);
    Scorches1.Save(stream);
    Scorches2.Save(stream);
    Scorches3.Save(stream);
    Scorches4.Save(stream);
    Shipyard.Save(stream);
    unknown_7c8.Save(stream);
    BuildPower.Save(stream);
    BuildRefinery.Save(stream);
    BuildBarracks.Save(stream);
    BuildTech.Save(stream);
    BuildWeapons.Save(stream);
    BuildDefense.Save(stream);
    BuildPDefense.Save(stream);
    BuildAA.Save(stream);
    BuildHelipad.Save(stream);
    BuildRadar.Save(stream);
    ConcreteWalls.Save(stream);
    NSGates.Save(stream);
    EWGates.Save(stream);
    BuildNavalYard.Save(stream);
    BuildDummy.Save(stream);
    NeutralTechBuildings.Save(stream);
    PadAircraft.Save(stream);
    OnFire.Save(stream);
    TreeFire.Save(stream);
    SplashList.Save(stream);
    BaseUnit.Save(stream);
    DefaultMirageDisguises.Save(stream);
    unknown_9ec.Save(stream);
    DeadBodies.Save(stream);
    DropPod.Save(stream);
    MetallicDebris.Save(stream);
    BridgeExplosions.Save(stream);
    IceCrackSounds.Save(stream);
    HSBuilding.Save(stream);
    AmerParaDropInf.Save(stream);
    AmerParaDropNum.Save(stream);
    AllyParaDropInf.Save(stream);
    AllyParaDropNum.Save(stream);
    SovParaDropInf.Save(stream);
    SovParaDropNum.Save(stream);
    DamageFireTypes.Save(stream);
    WeatherConClouds.Save(stream);
    WeatherConBolts.Save(stream);
}
