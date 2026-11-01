// int __fastcall Calculate_Projectile_Speed(int range, double gravity) -- 0x0047FB70
// TibSun combat.cpp: sqrt(range * gravity * 1.2).
#include "shared/weapon_type.hpp"
#include "shared/facing.hpp"
#include "shared/rules.hpp"
#include "shared/fast_math.hpp"
#include "shared/unknown_geometry.hpp"
#include "shared/combat.hpp"

int __fastcall Unknown_0047FB70(int range, double speed)
{
    return (int)unknown_sqrt_4ba410((double)range * speed * 1.2);
}
// @ref __real@8@3fff9999999999999800=0079dda8
// @ref ?unknown_sqrt_4ba410@@YANN@Z=004ba410
// @ref __ftol=0077f110
