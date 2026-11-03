// int TechnoClass::unknown_slot174(AbstractClass *target) (0x006C1380, slot 174)
// Which weapon to use against target: 0 primary, 1 secondary (TibSun's
// What_Weapon_Should_I_Use, with RA2's rules: a turret weapon set keeps the
// current index, occupied buildings follow the occupant's house, ...).
// The armor index is one named local read twice (TibSun's `armor`); read
// in place, this and target trade esi/edi.
#include "shared/techno.hpp"
#include "shared/techno_type.hpp"
#include "shared/weapon_type.hpp"
#include "shared/warhead_type.hpp"
#include "shared/bullet_type.hpp"
#include "shared/house.hpp"
#include "shared/infantry.hpp"
#include "shared/cell.hpp"
#include "shared/aircraft.hpp"
#include "shared/building_type_class.hpp"
// @ref __real@8@00000000000000000000=0079b610

int TechnoClass::unknown_slot174(AbstractClass *target)
{
    if (unknown_slot32()->Has_Turret_Weapons()) {
        return unknown_10c != -1 ? unknown_10c : 0;
    }
    WeaponTypeClass *secondary = unknown_slot231(1)->WeaponType;
    if (secondary == 0) {
        return 0;
    }
    WeaponTypeClass *primary = unknown_slot231(0)->WeaponType;
    if (primary == 0) {
        return 0;
    }
    if (secondary->unknown_112) {
        return 0;
    }
    if (secondary->unknown_126 && unknown_slot91() == 0x10) {
        return 1;
    }
    if (Kind_Of() == 6 && ((BuildingClass *)this)->unknown_531) {
        return 1;
    }
    if (Kind_Of() == 6 && ((BuildingClass *)this)->unknown_4532f0() > 0) {
        return ((BuildingClass *)this)->unknown_554[0]->House->unknown_130 == 1;
    }
    if (target == 0) {
        return 0;
    }
    if (target->Kind_Of() == 6 && House->Is_Ally((ObjectClass const *)target)
        && secondary->Warhead->ElectricAssault && ((BuildingClass *)target)->Type->Overpowerable) {
        return 1;
    }
    if (Kind_Of() == 2 && ((AircraftClass *)this)->unknown_5b2) {
        return 1;
    }
    if (!target->AbstractFlags.IsTechno) {
        return 0;
    }
    ObjectClass *object = (ObjectClass *)target;
    int armor = object->unknown_slot32()->unknown_9c;
    if (secondary->Warhead->Verses[armor] == 0.0) {
        return 0;
    }
    armor = object->unknown_slot32()->unknown_9c;
    if (primary->Warhead->Verses[armor] == 0.0) {
        return 1;
    }
    bool ground = ((CellClass *)object->unknown_slot105())->unknown_ec == 2
        || ((CellClass *)object->unknown_slot105())->unknown_ec == 6;
    if (object->unknown_slot21()) {
        ground = false;
    }
    if (!object->unknown_79 && ground) {
        int which = unknown_slot175(object);
        if (which == -1) {
            which = 0;
        }
        return which;
    } else if (secondary->Projectile->AA && object->unknown_slot21()) {
        return 1;
    }
    return 0;
}
