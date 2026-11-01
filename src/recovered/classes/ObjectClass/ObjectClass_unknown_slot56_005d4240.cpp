// bool ObjectClass::unknown_slot56(CoordStruct const &coord) (0x005D4240, slot 56)
// Places the object at coord with an arrival animation: refused off the map
// (0x0055A7F0), without a cell, on a bridge cell lacking 0x200, or, for a
// techno, when the cell is not enterable for its SpeedType in the zone of its
// MovementZone (0x0054F8F0, 0x00478760); then slot 53 (facing 0x80) and slot
// 103 at coord, and a new animation (rules +0xA78 for kind 8, else +0xA7C
// 0x4B above coord) attached to the object; for other kinds it also takes
// slot 115 (+0xBC) and the cell's +0x10A (+0xE4). +0x7A is set, and +0x79 on
// a bridge cell.
#include "shared/object_type.hpp"
#include "shared/techno.hpp"
#include "shared/techno_type.hpp"
#include "shared/anim.hpp"
#include "shared/rules.hpp"
#include "shared/techno_map.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Unknown_0055A7F0@MapClass@@QAE_NABUCoordStruct@@@Z=0055a7f0
// @ref ??AMapClass@@QAEAAVCellClass@@ABUCoordStruct@@@Z=00548000
// @ref ?Zone@MapClass@@QAEHABVCell@@H_N@Z=0054f8f0
// @ref ?Unknown_00478760@UnknownCellClass@@QAE_NHHHHHHH@Z=00478760
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ??2@YAPAXI@Z=00782017
// @ref ??0AnimClass@@QAE@PBVAnimTypeClass@@ABUCoordStruct@@HHHH@Z=00420110
// @ref ?Attach_To@AnimClass@@QAEXPAVObjectClass@@@Z=00422540

bool ObjectClass::unknown_slot56(CoordStruct const &coord)
{
    if (Map.Unknown_0055A7F0(coord)) {
        unknown_7a = true;
        UnknownCellClass *cell = Map_Cell(coord);
        if (cell != 0 && (!(cell->Flags & 0x100) || (unknown_79 = true, (cell->Flags & 0x200) != 0))) {
            bool techno;
            if (this != 0) {
                techno = unknown_14_bit0;
            }
            bool clear = true;
            if (this != 0 && techno) {
                int zone = unknown_slot32()->MovementZone;
                Cell position = Cell(coord.X / 256, coord.Y / 256);
                clear = cell->Unknown_00478760(unknown_slot32()->SpeedType, 0, 0,
                    Map.Zone(position, zone, unknown_79), zone, -1, 1);
            }
            if (clear) {
                if (unknown_slot53(&coord, 0x80)) {
                    unknown_slot103(coord);
                    AnimClass *anim;
                    if (Kind_Of() == 8) {
                        anim = new AnimClass(Rules->unknown_a78, coord, 0, 1, 0x600, 0);
                    } else {
                        CoordStruct above = coord;
                        above.Z += 0x4B;
                        anim = new AnimClass(Rules->unknown_a7c, above, 0, 1, 0x600, 0);
                    }
                    if (anim != 0) {
                        anim->Attach_To(this);
                        if (Kind_Of() != 8) {
                            anim->unknown_bc = unknown_slot115();
                            anim->unknown_e4 = ((UnknownCellClass *)unknown_slot105())->unknown_10a;
                        }
                    }
                    return true;
                }
            }
        }
    }
    return false;
}
