// double Get_Floater_Gravity() -- 0x0047FCD0
// TibSun combat.cpp: half the rules gravity.
#include "shared/weapon_type.hpp"
#include "shared/facing.hpp"
#include "shared/rules.hpp"
#include "shared/fast_math.hpp"
#include "shared/unknown_geometry.hpp"
#include "shared/combat.hpp"

double __cdecl Unknown_0047FCD0()
{
    return Rules->unknown_1320 * 0.5;
}
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref __real@8@3ffe8000000000000000=0079a728
