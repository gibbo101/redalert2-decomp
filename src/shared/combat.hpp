// combat.cpp (0x0047E1C0-0x0047FCE1; TibSun combat.cpp): damage, explosions and ballistic solutions.
// Declarations the other units' headers do not already carry.
#ifndef RA2_SHARED_COMBAT_HPP
#define RA2_SHARED_COMBAT_HPP

#include "shared/facing.hpp"

// The elevation angle (radians) that drops a shot onto a target at a horizontal distance and a
// height difference (0x0047F9B0; TibSun Calculate_Projectile_Angle; a target above the shooter
// always gets a 45 degree solution).
bool __fastcall Calculate_Projectile_Angle(bool high_arc, int speed, int distance, int height, double gravity, double &angle);
// The flat solution as a direction, normalised to [0, 2pi) before the conversion (0x0047FB00;
// no direct callers; hypothesis).
bool __fastcall Calculate_Projectile_Pitch_Flat(int speed, int distance, int height, double gravity, struct UnknownFacingDir *pitch);
// Whether any ballistic solution exists (0x0047FBA0; TibSun Is_Projectile_Trajectory_Valid).
bool __fastcall Is_Projectile_Trajectory_Valid(int speed, int distance, int height, double gravity);

// Explosion_Damage at every cell within a radius, scaled down with the distance from the centre
// (0x0047F6E0; TibSun Wide_Area_Damage without the terrain deformation; no direct callers).
class TechnoClass;
class WarheadTypeClass;
void __fastcall Wide_Area_Damage(CoordStruct const &coord, int radius, int rawdamage, TechnoClass *source, WarheadTypeClass *warhead);

// The frame time used by the light-detail test (0x0053D840; owner unit unknown; hypothesis).
unsigned int Unknown_0053D840();

// The binary angle of a radian angle (TibSun DirType::From_Radian: 65534 units per turn).
inline void UnknownFacingDir::From_Radian(double angle)
{
    Raw = (unsigned short)(short)((angle - 1.5707963267948966) * -10430.060040584269);
}

#endif
