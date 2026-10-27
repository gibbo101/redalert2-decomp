// void AnimClass::unknown_func_422f50() (0x00422F50)
// Vein damage: the animation is done (unknown_17b) unless its cell is a
// grown vein cell (+0x44 == 0x7E, +0x11E >= 0x30, +0x11C clear) holding a
// harmless first object (slot 108 <= 0). On even frames every techno in the
// cell that is not immune to veins, not in state 8, alive, on the map
// (unknown_7d) and low (slot 108 <= 5) takes the rules' vein damage
// (+0xE4) with the veins' warhead (+0xCB0).
#include "shared/anim.hpp"
#include "shared/map_view.hpp"
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?Unknown_0040DC20@ObjectClass@@QAEPAVTechnoClass@@XZ=0040dc20
// @ref ?Unknown_006D7910@UnknownAnimTechno@@QAE_NH@Z=006d7910

void AnimClass::unknown_func_422f50()
{
    CoordStruct coord = Coord;
    UnknownAnimCell *cell = (UnknownAnimCell *)&Map[coord];
    ObjectClass *object = cell->unknown_e4;
    if (object == 0 || object->unknown_slot108() > 0 || cell->unknown_44 != 0x7E ||
        cell->unknown_11e < 0x30 || cell->unknown_11c) {
        unknown_17b = true;
    }
    if (!(Frame & 1)) {
        while (object != 0) {
            ObjectClass *next = object->unknown_30;
            int damage = Rules->unknown_e4;
            UnknownAnimTechno *techno = (UnknownAnimTechno *)object->As_Techno();
            if (techno != 0 && !((UnknownAnimTechnoType *)techno->unknown_slot32())->ImmuneToVeins &&
                !techno->Unknown_006D7910(8) && techno->Strength > 0 && techno->unknown_7d &&
                techno->unknown_slot108() <= 5) {
                techno->unknown_slot86(&damage, 0, (WarheadTypeClass *)Rules->unknown_cb0, 0, 0, 0);
            }
            object = next;
        }
    }
}
