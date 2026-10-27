// bool SidebarClass::StripClass::Unknown_0067EA20(int type, int id, int other_type, int other_id) (0x0067EA20)
// The strip's sort order: whether the buildable (type, id) goes before
// (other_type, other_id). Superweapons (kinds 0x1F, 0x20, 0x39) come
// first, by recharge time then name; then the player's side's own types;
// then ground units, aircraft and naval units (kinds 3 and 0x28 by
// ConsideredAircraft and Naval); then by tech level, cost and name.
#include "shared/sidebar.hpp"
#include "shared/techno_type.hpp"
#include "shared/house_type.hpp"
#include "shared/super_weapon_type.hpp"
// @ref ?Unknown_00482C00@@YIPAVObjectTypeClass@@HH@Z=00482c00
// @ref ?SuperWeaponTypes@@3V?$DynamicVectorClass@PAVSuperWeaponTypeClass@@@@A=00a40338
// @ref ?unknown_player_a35db4@@3PAVHouseClass@@A=00a35db4
// @ref _wcscmp=007837d3

extern "C" int __cdecl wcscmp(wchar_t const *string1, wchar_t const *string2);   // 0x007837D3

bool SidebarClass::StripClass::Unknown_0067EA20(int type, int id, int other_type, int other_id)
{
    TechnoTypeClass *techno = (TechnoTypeClass *)Unknown_00482C00(type, id);
    TechnoTypeClass *other = (TechnoTypeClass *)Unknown_00482C00(other_type, other_id);
    wchar_t const *name;
    wchar_t const *other_name;
    if (other_type == 0) {
        return true;
    }

    bool super = type == 0x1F || type == 0x39 || type == 0x20;
    bool other_super = other_type == 0x1F || other_type == 0x39 || other_type == 0x20;
    if (super) {
        if (other_super) {
            SuperWeaponTypeClass *weapon = SuperWeaponTypes[id];
            SuperWeaponTypeClass *other_weapon = SuperWeaponTypes[other_id];
            if (weapon->RechargeTime < other_weapon->RechargeTime) {
                return true;
            }
            if (weapon->RechargeTime > other_weapon->RechargeTime) {
                return false;
            }
            name = weapon->UIName;
            other_name = other_weapon->UIName;
            return wcscmp(name, other_name) <= 0 ? true : false;
        }
    } else if (!other_super) {
        int side = unknown_player_a35db4->Type->Side;
        bool own = side == techno->AIBasePlanningSide;
        bool other_own = side == other->AIBasePlanningSide;
        if (own && !other_own) {
            return true;
        }
        if (!own && other_own) {
            return false;
        }
    }

    bool unit = type == 0x28 || type == 3;
    bool aircraft = unit && techno->ConsideredAircraft;
    bool naval = unit && techno->Naval;
    bool ground = !aircraft && !naval;
    bool other_unit = other_type == 0x28 || other_type == 3;
    bool other_aircraft = other_unit && other->ConsideredAircraft;
    bool other_naval = other_unit && other->Naval;
    bool other_ground = !other_aircraft && !other_naval;

    if (super) {
        if (other_aircraft || other_naval || other_ground) {
            return true;
        }
    } else if (ground) {
        if (other_super) {
            return false;
        }
        if (other_aircraft || other_naval) {
            return true;
        }
    } else if (aircraft) {
        if (other_super) {
            return false;
        }
        if (other_ground) {
            return false;
        }
        if (other_naval) {
            return true;
        }
    } else if (naval) {
        if (other_super) {
            return false;
        }
        if (other_ground || other_aircraft) {
            return false;
        }
    }

    if (techno->TechLevel < other->TechLevel) {
        return true;
    }
    if (techno->TechLevel > other->TechLevel) {
        return false;
    }
    int cost = techno->unknown_slot33((int)unknown_player_a35db4);
    int other_cost = other->unknown_slot33((int)unknown_player_a35db4);
    if (cost < other_cost) {
        return true;
    }
    if (cost > other_cost) {
        return false;
    }
    name = techno->UIName;
    other_name = other->UIName;
    return wcscmp(name, other_name) <= 0 ? true : false;
}
