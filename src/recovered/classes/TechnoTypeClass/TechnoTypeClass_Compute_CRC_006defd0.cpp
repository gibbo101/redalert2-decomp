// void TechnoTypeClass::Compute_CRC(WWCRCEngine &crc) const (0x006DEFD0)
// The base CRC, then the rules values in Westwood's order (list counts,
// not their elements).
#include "shared/techno_type.hpp"
#include "shared/house.hpp"
// @ref ?Compute_CRC@AbstractTypeClass@@UBEXAAVWWCRCEngine@@@Z=00410960
// @ref ??RWWCRCEngine@@QAEXN@Z=00493f70
// @ref ??RWWCRCEngine@@QAEXJ@Z=00493f30
// @ref ??RWWCRCEngine@@QAEJPBXH@Z=00493fc0
// @ref ??RWWCRCEngine@@QAEX_N@Z=00493e80
// @ref ??RWWCRCEngine@@QAEXD@Z=00493df0

void TechnoTypeClass::Compute_CRC(WWCRCEngine &crc) const
{
    AbstractTypeClass::Compute_CRC(crc);
    crc(ThreatAvoidanceCoefficient);
    crc((long)SlowdownDistance);
    crc(DeaccelerationFactor);
    crc(AccelerationFactor);
    crc((long)CloakingSpeed);
    crc((long)DebrisTypes.Count());
    crc((long)DebrisAnims.Count());
    crc((long)Dock.Count());
    crc((long)DebrisMaximums.Count());
    crc(&Locomotor, sizeof(Locomotor));
    crc(unknown_330);
    crc(unknown_338);
    crc(Weight);
    crc(PhysicalSize);
    crc(Size);
    crc(SizeLimit);
    crc(HoverAttack);
    crc((long)unknown_368);
    crc(ImmuneToVeins);
    crc(TiberiumHeal);
    crc(TargetLaser);
    crc(RollAngle);
    crc(PitchAngle);
    crc(PitchSpeed);
    crc((long)FlightLevel);
    crc((long)BuildLimit);
    crc((long)Category);
    crc(DeployTime);
    crc((long)FireAngle);
    crc((long)PipScale);
    crc((long)VoiceSelect.Count());
    crc((long)VoiceMove.Count());
    crc((long)VoiceAttack.Count());
    crc((long)VoiceSpecialAttack.Count());
    crc((long)VoiceDie.Count());
    crc((long)VoiceFeedback.Count());
    crc((long)MoveSound.Count());
    crc((long)DieSound.Count());
    crc((long)DamageParticleSystems.Count());
    crc((long)DestroyParticleSystems.Count());
    crc((long)MovementZone);
    crc((long)GuardRange.Value);
    crc((long)MaxDebris);
    crc((long)MinDebris);
    crc((long)Passengers);
    crc((long)Sight);
    crc((long)Cost);
    crc((long)Soylent);
    crc((long)TechLevel);
    crc((long)Prerequisite.Count());
    crc((long)PrerequisiteOverride.Count());
    crc((long)ThreatPosed);
    crc((long)unknown_59c);
    crc((long)Speed);
    crc((long)SpeedType);
    crc((long)Ammo);
    crc((long)AirRangeBonus);
    crc((long)Owner);
    crc((long)AIBasePlanningSide);
    crc((long)RotCount);
    crc((long)ROT);
    crc((long)TurretOffset);
    crc((long)Points);
    crc((long)Explosion.Count());
    crc((long)DestroyAnim.Count());
    crc((long)ShadowIndex);
    crc((long)Storage);
    crc(IsTrain);
    crc(IsDropship);
    crc(ToProtect);
    crc(Disableable);
    crc(unknown_aa4);
    crc(DoubleOwned);
    crc(Invisible);
    crc(RadarVisible);
    crc(unknown_aa8);
    crc(Sensors);
    crc(Nominal);
    crc(Turret);
    crc(Repairable);
    crc(Crewed);
    crc(Remapable);
    crc(Cloakable);
    crc(GapGenerator);
    crc(GapRadiusInCells);
    crc(SuperGapRadiusInCells);
    crc(Teleporter);
    crc(SelfHealing);
    crc(Explodes);
    crc(NoAutoFire);
    crc(TurretSpins);
    crc(Normalized);
    crc(ManualReload);
    crc(VisibleLoad);
    crc(LightningRod);
    crc(DisableVoxelCache);
    crc(DisableShadowCache);
    crc(MobileFire);
    crc(OpportunityFire);
    crc(DistributedFire);
}
