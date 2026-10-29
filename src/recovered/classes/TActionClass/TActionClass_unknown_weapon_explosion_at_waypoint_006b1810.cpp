// bool TActionClass::unknown_weapon_explosion_at_waypoint(...) (0x006B1810)
// The explosion of weapon type Data at waypoint +0x44 (ground height, raised on a bridge): its warhead's damage animation, Unknown_0047F600 and Unknown_0047E2C0 with the weapon's +0xA4 damage; always true.
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#include "shared/vector_class.hpp"
#include "shared/taction.hpp"
#include "shared/id_source.hpp"
#include "shared/map_cell.hpp"
#include "shared/map_view.hpp"
#include "shared/unknown_geometry.hpp"
#include "shared/anim.hpp"
#include "shared/weapon_type.hpp"
// @ref ?Get_Waypoint_Location@UnknownIDSource@@QBE?AVCell@@H@Z=00663180
// @ref ?Select_Damage_Anim@@YIPAVAnimTypeClass@@HPAVWarheadTypeClass@@HPAUCoordStruct@@@Z=0047f4d0
// @ref ?Unknown_0047FCC0@@YGHUCoordStruct@@@Z=0047fcc0
// @ref ?Unknown_0047F600@@YIXUCoordStruct@@HPAVWarheadTypeClass@@HH@Z=0047f600
// @ref ?Unknown_0047E2C0@@YIXABUCoordStruct@@HHPAVWarheadTypeClass@@H@Z=0047e2c0
// @ref _unknown_geometry_j=00abfdf8

bool TActionClass::unknown_weapon_explosion_at_waypoint(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell)
{
    Cell waypoint = unknown_id_source_a3d290->Get_Waypoint_Location(unknown_44);
    CoordStruct coord = Cell_Center(waypoint);
    coord.Z = Map.Unknown_0055A280(coord);
    if ((Map[waypoint].unknown_140 & 0x100) || (Map[waypoint].unknown_140 & 0x400)) {
        coord.Z += unknown_geometry_j;
    }
    int index = Data;
    WeaponTypeClass *weapon = unknown_WeaponTypeClass_list_00839b90[index];
    int damage = weapon->unknown_a4;
    int land = Map[coord].unknown_ec;
    AnimTypeClass *anim = Select_Damage_Anim(damage, weapon->Warhead, land, &coord);
    if (anim != 0) {
        new AnimClass(anim, coord, 0, 1, 0x2600, Unknown_0047FCC0(coord));
    }
    Unknown_0047F600(coord, damage, unknown_WeaponTypeClass_list_00839b90[index]->Warhead, 0, 0);
    Unknown_0047E2C0(coord, damage, 0, unknown_WeaponTypeClass_list_00839b90[index]->Warhead, 1);
    return true;
}
