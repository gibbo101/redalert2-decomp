// void BuildingTypeClass::Compute_CRC(WWCRCEngine &crc) const (0x0045D8F0)
// The techno CRC, then the building values in Westwood's order.
#include "shared/building_type.hpp"
// @ref ?Compute_CRC@TechnoTypeClass@@UBEXAAVWWCRCEngine@@@Z=006defd0
// @ref ??RWWCRCEngine@@QAEXN@Z=00493f70
// @ref ??RWWCRCEngine@@QAEXJ@Z=00493f30
// @ref ??RWWCRCEngine@@QAEXPBD@Z=00493f90
// @ref ??RWWCRCEngine@@QAEJPBXH@Z=00493fc0
// @ref ??RWWCRCEngine@@QAEX_N@Z=00493e80

void BuildingTypeClass::Compute_CRC(WWCRCEngine &crc) const
{
    TechnoTypeClass::Compute_CRC(crc);
    crc(GateCloseDelay);
    crc((long)LightVisibility);
    crc((long)LightIntensity);
    crc((long)LightRedTint);
    crc((long)LightGreenTint);
    crc((long)LightBlueTint);
    crc(BuildupFile);
    crc(PowersUpBuilding);
    crc((long)Adjacent);
    crc((long)Factory);
    crc((long)Power);
    crc((long)PowerDrain_c6c);
    crc((long)ExtraPower);
    crc((long)ExtraPowerDrain_c74);
    crc((long)Foundation);
    crc((long)Height);
    crc((long)OccupyHeight);
    crc((long)MidPoint);
    crc((long)DoorStages);
    crc(AnimFrames, sizeof(AnimFrames));
    crc(Anims, sizeof(Anims));
    crc((long)Upgrades);
    crc((long)SpecialZOverlayZAdjust);
    crc(HoverPad);
    crc(IsPlug);
    crc(IsTemple);
    crc(HasSpotlight);
    crc(BaseNormal);
    crc(EligibileForAllyBuilding);
    crc(NeedsEngineer);
    crc(Bib);
    crc(Wall);
    crc(Capturable);
    crc(Powered);
    crc(Unsellable);
    crc(Radar);
    crc(SpySat);
    crc(ChargeAnim);
    crc(IsAnimDelayedFire);
    crc((long)DelayedFireDelay);
    crc(SiloDamage);
    crc(UnitRepair);
    crc(UnitReload);
    crc(Cloning);
    crc(Flat);
    crc(DockUnload);
    crc(Recoilless);
    crc(BridgeRepairHut);
    crc(Gate);
    crc(SAM);
    crc(ConstructionYard);
    crc(NukeSilo);
    crc(Refinery);
    crc(WeaponsFactory);
    crc(LaserFencePost);
    crc(LaserFence);
    crc(FirestormWall);
    crc(Helipad);
    crc(OrePurifier);
    crc(ExtraDamageStage);
    crc(Hospital);
    crc(Armory);
    crc((long)GateStages);
    crc((long)PowersUpToLevel);
    crc(DamagedDoor);
    crc(InvisibleInGame);
    crc(TerrainPalette);
    crc(TurretAnimIsVoxel);
    crc(BarrelAnimIsVoxel);
    crc(VoxelBarrelFile);
    crc(unknown_13a8);
    crc(&VoxelBarrelOffsetToPitchPivotPoint, sizeof(VoxelBarrelOffsetToPitchPivotPoint));
    crc(&VoxelBarrelOffsetToRotatePivotPoint, sizeof(VoxelBarrelOffsetToRotatePivotPoint));
    crc(&VoxelBarrelOffsetToBuildingPivotPoint, sizeof(VoxelBarrelOffsetToBuildingPivotPoint));
    crc(&VoxelBarrelOffsetToBarrelEnd, sizeof(VoxelBarrelOffsetToBarrelEnd));
    crc(CrateBeneath);
    crc(LeaveRubble);
    crc(CrateBeneathIsMoney);
    crc((long)NumberOfDocks);
    crc((long)BarrelStartPitch);
    crc(ConcentricRadialIndicator);
}
