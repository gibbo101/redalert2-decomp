// void __fastcall Combat_Lighting(CoordStruct coord, int damage, WarheadTypeClass *warhead, bool forced, int flags) -- 0x0047F600
// TibSun combat.cpp Combat_Lighting in RA2 form: when lighting detail allows it (or flags carry a light
// kind), a forced or Bright warhead makes a SpotLightClass, sized by CombatLightSize (capped at 1,
// times 63) or else by the damage clamped to 21..63, tagged with flags. The callers pass forced in a
// full word; only its low byte is tested.
#include "shared/anim.hpp"
#include "shared/warhead_type.hpp"
#include "shared/spot_light.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/queue.hpp"
#include "shared/combat.hpp"

void __fastcall Unknown_0047F600(CoordStruct coord, int damage, WarheadTypeClass *warhead, int forced, int flags)
{
    if ((unknown_a40b2c != 0 && unknown_a6eb1c >= Unknown_0053D840()) || (flags & 0xF) != 0) {
        if ((char)forced || warhead != 0 && warhead->Bright) {
            int size;
            float light = warhead->CombatLightSize;
            if (light > 0.0f) {
                if (light > 1.0f) {
                    light = 1.0f;
                }
                size = (int)(light * 63.0f);
            } else {
                damage *= 64;
                size = damage >> 8;
                if (size >= 63) {
                    size = 63;
                } else if (size <= 21) {
                    size = 21;
                }
            }
            (new SpotLightClass(coord, size))->unknown_14 |= flags;
        }
    }
}
// @ref __real@4@4004fc00000000000000=0079dda4
// @ref ?Unknown_0053D840@@YAIXZ=0053d840
