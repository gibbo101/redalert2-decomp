// int TechnoClass::unknown_slot115() (0x006D1480, slot 115)
// The color scheme value (+0x30C of a 0x00AB6EF8 entry) to draw with: from
// the type's own palette list when it has one, else the owner's scheme, or
// slot 51's house's when slot 245 rejects the player.
#include "shared/techno.hpp"
#include "shared/anim.hpp"
// @ref ?unknown_list_ab6ef8@@3V?$DynamicVectorClass@PAUUnknownAB6EF8Entry@@@@A=00ab6ef8
// @ref ?unknown_player_a35db4@@3PAVHouseClass@@A=00a35db4

int TechnoClass::unknown_slot115()
{
    TechnoTypeClass *type = unknown_slot32();
    int scheme = House->ColorSchemeIndex;
    DynamicVectorClass<UnknownAB6EF8Entry *> *palette = (DynamicVectorClass<UnknownAB6EF8Entry *> *)type->Palette;
    if (palette != 0) {
        return (*palette)[scheme]->unknown_30c;
    }
    if (!unknown_slot245(unknown_player_a35db4) && unknown_slot51(true) != 0) {
        return unknown_list_ab6ef8[unknown_slot51(true)->ColorSchemeIndex]->unknown_30c;
    }
    return unknown_list_ab6ef8[scheme]->unknown_30c;
}
