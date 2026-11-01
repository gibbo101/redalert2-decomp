// bool __fastcall Calculate_Projectile_Pitch_Flat(int speed, int distance, int height, double gravity, UnknownFacingDir *pitch) -- 0x0047FB00
// The flat solution only, normalised to [0, 2pi) before the conversion (no direct callers).
#include "shared/weapon_type.hpp"
#include "shared/facing.hpp"
#include "shared/rules.hpp"
#include "shared/fast_math.hpp"
#include "shared/unknown_geometry.hpp"
#include "shared/combat.hpp"

bool __fastcall Calculate_Projectile_Pitch_Flat(int speed, int distance, int height, double gravity, UnknownFacingDir *pitch)
{
    double angle;
    if (Calculate_Projectile_Angle(false, speed, distance, height, gravity, angle)) {
        if (angle < 0.0) {
            angle += 6.283185307179586;
        }
        UnknownFacingDir dir;
        dir.From_Radian(angle);
        *pitch = dir;
        return true;
    }
    return false;
}
// @ref __real@8@00000000000000000000=0079b610
// @ref __real@8@3fffc90fdaa22168c000=0079b630
// @ref __real@8@4001c90fdaa22168c000=0079c9b8
// @ref __real@8@c00ca2f83d7b47677800=0079b628
// @ref ?Calculate_Projectile_Angle@@YI_N_NHHHNAAN@Z=0047f9b0
// @ref __ftol=0077f110
