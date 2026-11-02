// int TechnoClass::unknown_slot28(ObjectClass *object, bool arg2) (0x006CC5D0, slot 28)
// The action against an object (Red Alert's What_Action(ObjectClass const *)):
// none for no object; a passenger-style techno (slot 111) only selects; the
// one selected object detonating its own bomb (0x37), self actions (4), the
// force-move (8), force-fire and select-key overrides (0x1A, 1), then the
// attack (5) when the weapon can (slot 218 is not 5, a spy or engineer's
// building target, or force-fire), else select (7) or none.
#include "shared/techno.hpp"
#include "shared/techno_type.hpp"
#include "shared/house.hpp"
#include "shared/keyboard.hpp"
#include "shared/rules.hpp"
#include "shared/weapon_type.hpp"
#include "shared/warhead_type.hpp"
#include "shared/infantry.hpp"
#include "shared/infantry_type.hpp"
#include "shared/aircraft.hpp"
// @ref ?WWKeyboard@@3PAVWWKeyboardClass@@A=00832468
// @ref ?Down@WWKeyboardClass@@QAE_NG@Z=00532890
// @ref ?unknown_key_a40ba4@@3HA=00a40ba4
// @ref ?unknown_key_a40ba8@@3HA=00a40ba8
// @ref ?KeyForceFire1@@3HA=00a40bac
// @ref ?KeyForceFire2@@3HA=00a40bb0
// @ref ?KeyForceMove1@@3HA=00a40bb4
// @ref ?KeyForceMove2@@3HA=00a40bb8
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?unknown_player_a35db4@@3PAVHouseClass@@A=00a35db4
// @ref ?unknown_game_mode_a3d298@@3HA=00a3d298
// @ref ?Frame@@3HA=00a40d2c
// @ref ?Unknown_00435FF0@BombClass@@QBEHXZ=00435ff0

// A key binding is down (the bindings are ints; WWKeyboardClass takes 16-bit keys).
inline bool Techno_Key_Down(int key) { return WWKeyboard->Down(key); }

int TechnoClass::unknown_slot28(ObjectClass *object, bool arg2)
{
    if (object == 0) {
        return 0;
    }
    if (unknown_slot111()) {
        if (unknown_slot163() && House->Unknown_004F52B0() && object->Owner() != Owner()) {
            return 0;
        }
        if (unknown_32c && unknown_372) {
            return 0;
        }
        if (!object->unknown_slot76() || object->unknown_77) {
            return 0;
        }
        return 7;
    }
    if (object == this && unknown_objects_a40c60.Count() == 1 && object->unknown_38 != 0 && object->unknown_38->unknown_28->Unknown_004F52B0()) {
        if (object->unknown_38->Unknown_00435FF0() == 1 && Rules->CanDetonateDeathBomb) {
            return 0x37;
        }
        if (object->unknown_38->Unknown_00435FF0() == 0 && Rules->CanDetonateTimeBomb) {
            return 0x37;
        }
    }
    bool third = !arg2 && (Techno_Key_Down(unknown_key_a40ba4) || Techno_Key_Down(unknown_key_a40ba8));
    bool force_fire = !arg2 && (Techno_Key_Down(KeyForceFire1) || Techno_Key_Down(KeyForceFire2));
    if (!arg2 && (Techno_Key_Down(KeyForceMove1) || Techno_Key_Down(KeyForceMove2))) {
        if (force_fire) {
            force_fire = false;
        } else if (House->Unknown_004F52B0() && !unknown_32c) {
            return 8;
        }
    }
    if (object == this && unknown_objects_a40c60.Count() == 1 && House->Unknown_004F52B0()) {
        return 4;
    }
    if (object == this && unknown_objects_a40c60.Count() == 1 && House->Is_Ally(unknown_player_a35db4) && unknown_game_mode_a3d298 == 0) {
        if (this != 0) {
            if (Kind_Of() == 1 && ((UnitClass *)this)->Type->Passengers > 0 && Cargo.Count > 0) {
                return 4;
            }
            if (Kind_Of() == 2 && ((AircraftClass *)this)->unknown_5b1) {
                return 4;
            }
        }
    }
    if (House->Unknown_004F52B0() && House->Is_Ally((TechnoClass *)object) && Kind_Of() != 2 && force_fire) {
        if (!third) {
            goto attack;
        }
        if (unknown_slot39()) {
            return 0x1A;
        }
    }
    if (third && House->Unknown_004F52B0() && unknown_slot39()) {
        return 1;
    }
attack:
    {
        TechnoTypeClass *type = unknown_slot32();
        int weapon = unknown_slot174(object);
        if (object->unknown_slot30()) {
            WeaponTypeClass *weapon_type = unknown_slot231(weapon)->WeaponType;
            bool disguised = Rules->AttackCursorOnDisguise
                || (object->AbstractFlags.IsTechno && (object->unknown_slot32()->PermaDisguise
                    || (object->AbstractFlags.IsTechno && ((TechnoClass *)object)->unknown_184.Value() != 0)));
            bool owned = object->unknown_slot49(House) && !disguised;
            bool capture = owned && object->unknown_slot51(true) == 0;
            bool can208 = unknown_slot208(object);
            bool usable = !owned || (capture && can208);
            bool ivan = weapon_type != 0 && weapon_type->Warhead->IvanBomb && object->unknown_slot32() != 0
                && object->unknown_slot32()->Passengers > 0;
            bool foot = false;
            if (weapon_type != 0 && weapon_type->Warhead->Sonic) {
                foot = object->AbstractFlags.IsFoot;
            }
            bool sonic = foot && ((FootClass *)object)->unknown_580 != 0;
            bool friendly = unknown_slot32()->AttackFriendlies || (unknown_slot32()->AttackCursorOnFriendlies && !ivan) || sonic;
            bool enemy = !House->Is_Ally((TechnoClass *)object) || friendly;
            bool owned_friendly = owned && friendly;
            if (House->Unknown_004F52B0()) {
                if (force_fire || (enemy && (usable || owned_friendly) && (object->Class_Of()->unknown_201 || can208))) {
                    bool infiltrate = Kind_Of() == 15 && ((InfantryTypeClass *)type)->Infiltrate;
                    if ((unknown_slot163() || infiltrate) && (unknown_slot39() || unknown_slot212(object, weapon))) {
                        bool special = false;
                        if (infiltrate) {
                            if ((!((InfantryClass *)this)->Type->Agent && object->Kind_Of() == 6 && ((BuildingClass *)object)->Type->Capturable)
                                || (((InfantryClass *)this)->Type->Agent && object->Kind_Of() == 6 && ((BuildingClass *)object)->Type->Spyable)
                                || (((InfantryClass *)this)->Type->C4 && object->Kind_Of() == 6 && ((BuildingClass *)object)->Type->CanC4)) {
                                special = true;
                            }
                        }
                        if (unknown_slot218(object, weapon, 1) != 5 || special || force_fire) {
                            return 5;
                        }
                    }
                }
            }
        }
    }
    if (unknown_slot163() && House->Unknown_004F52B0() && object->Owner() != Owner()) {
        return 0;
    }
    if (unknown_32c && unknown_372) {
        return 0;
    }
    if (!object->unknown_slot76() || object->unknown_77 || object->unknown_slot111()) {
        return 0;
    }
    return 7;
}
