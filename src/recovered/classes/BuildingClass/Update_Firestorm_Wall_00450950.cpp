// Refresh a Firestorm wall's neighbours, active animation, and crossing damage.
#include "shared/building.hpp"
#include "shared/building_map.hpp"
#include "shared/cell.hpp"
#include "shared/anim.hpp"
#include "shared/foot.hpp"
#include "shared/house.hpp"
#include "shared/rules.hpp"
// @ref ?unknown_475d60@CellClass@@=00475d60
// @ref ?Unknown_00472540@CellClass@@=00472540
// @ref ??0AnimClass@@=00420110
// @ref ?unknown_450cb0@BuildingClass@@=00450cb0
void BuildingClass::Update_Firestorm_Wall_00450950()
{
    bool active = false;
    if (!Type->FirestormWall) return;
    unsigned frame = unknown_4508c0();
    if (House->unknown_142) { frame += 32; active = true; }
    CellClass *cell = &Map[Position_Coord_00450950(*this)];
    if (frame != (unsigned)unknown_4f0) {
        unknown_4f0 = frame;
        unknown_75 = true;
        cell->Unknown_00472540(-1);
    }
    unsigned connections = frame & 15;
    if (active && connections != 10 && connections != 5 && !unknown_454[10]) {
        AnimClass *animation = new AnimClass(Rules->FirestormActiveAnim, Position_Coord_00450950(*this) - CoordStruct(128,128,0), 1, 0, 0x600, -10);
        unknown_454[10] = animation;
        animation->unknown_179 = unknown_5b7;
    } else if (unknown_454[10]) {
        delete unknown_454[10];
        unknown_454[10] = 0;
    }
    if (active) {
        ObjectClass *object = cell->OccupierPtr;
        while (object) {
            if (object != this && object->Class_Of() && !object->Class_Of()->unknown_209) {
                switch (object->Kind_Of()) {
                case 1: case 2: case 15: {
                    ObjectClass *next = object->unknown_30;
                    unknown_450cb0(object, true);
                    if (next) { object = next; continue; }
                    break;
                }
                }
            }
            object = object->unknown_30;
        }
        CoordStruct center = cell->unknown_475d60();
        for (int x=-2; x<3; ++x) {
            for (int y=-2; y<3; ++y) {
                Cell offset((short)x, (short)y);
                CellClass *neighbor = &Map[offset + cell->MapCoords];
                if (neighbor != cell) {
                    ObjectClass *occupier = neighbor->OccupierPtr;
                    while (occupier) {
                        ObjectClass *next = occupier->unknown_30;
                        bool is_foot;
                        if (occupier) is_foot = occupier->AbstractFlags.IsFoot;
                        if (occupier && is_foot && static_cast<FootClass *>(occupier)->Locomotor.Checked()->Is_Moving_Here(center) && !occupier->unknown_slot32()->unknown_209) {
                            int damage = occupier->Strength;
                            occupier->unknown_slot86(&damage, 0, Rules->unknown_c74, 0, true, 1);
                        }
                        occupier = next;
                    }
                }
            }
        }
    }
}
