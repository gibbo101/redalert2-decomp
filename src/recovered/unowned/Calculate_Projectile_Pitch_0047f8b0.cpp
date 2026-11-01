// bool __fastcall Calculate_Projectile_Pitch(bool high_arc, int speed, int distance, int height, double gravity, UnknownFacingDir *pitch) -- 0x0047F8B0
// TibSun combat.cpp Calculate_Projectile_Pitch: the angle from Calculate_Projectile_Angle as a
// direction; a flat shot is mirrored when one lepton further needs a smaller angle.
#include "shared/weapon_type.hpp"
#include "shared/facing.hpp"
#include "shared/rules.hpp"
#include "shared/fast_math.hpp"
#include "shared/unknown_geometry.hpp"
#include "shared/combat.hpp"

bool __fastcall Unknown_0047F8B0(bool high_arc, int speed, int distance, int height, double gravity, UnknownFacingDir *pitch)
{
    double angle;
    if (Calculate_Projectile_Angle(high_arc, speed, distance, height, gravity, angle)) {
        if (high_arc) {
            UnknownFacingDir dir;
            dir.From_Radian(angle);
            *pitch = dir;
            return true;
        }
        double test;
        Calculate_Projectile_Angle(false, speed, distance + 1, height, gravity, test);
        if (test < angle) {
            UnknownFacingDir dir;
            dir.From_Radian(-angle);
            *pitch = dir;
        } else {
            UnknownFacingDir dir;
            dir.From_Radian(angle);
            *pitch = dir;
        }
        return true;
    }
    return false;
}
// @ref __real@8@3fffc90fdaa22168c000=0079b630
// @ref __real@8@c00ca2f83d7b47677800=0079b628
// @ref ?Calculate_Projectile_Angle@@YI_N_NHHHNAAN@Z=0047f9b0
// @ref __ftol=0077f110
