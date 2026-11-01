// int __fastcall Modify_Damage(int damage, WarheadTypeClass *warhead, int armor, int distance) -- 0x0047E1C0
// TibSun combat.cpp Modify_Damage in RA2 form: no damage when inert; healing (negative damage) only
// within 8 leptons; otherwise the warhead's PercentAtMax fall-off over CellSpread, never below zero,
// scaled by Verses[armor] and capped at Rules MaxDamage.
#include "shared/warhead_type.hpp"
#include "shared/rules.hpp"
#include "shared/id_source.hpp"
#include "shared/special.hpp"

int __fastcall Unknown_0047E1C0(int damage, WarheadTypeClass *warhead, int armour, int distance)
{
    if (!damage || unknown_id_source_a3d290->Special().Inert || warhead == 0) {
        return 0;
    }
    if (damage < 0) {
        if (distance < 8) {
            return damage;
        }
        return 0;
    }
    float fdamage = (float)damage;
    float atmax = fdamage * warhead->PercentAtMax;
    int spread = (int)(warhead->CellSpread * 256.0f);
    if (atmax != fdamage && spread != 0) {
        damage = (int)((fdamage - atmax) * (spread - distance) / spread + atmax);
    }
    damage = damage > 0 ? damage : 0;
    damage = (int)(damage * warhead->Verses[armour]);
    damage = damage < Rules->MaxDamage ? damage : Rules->MaxDamage;
    return damage;
}
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref __real@4@40078000000000000000=0079b0ac
// @ref __ftol=0077f110
