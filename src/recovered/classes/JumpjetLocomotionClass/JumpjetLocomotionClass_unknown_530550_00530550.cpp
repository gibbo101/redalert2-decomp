// void JumpjetLocomotionClass::unknown_530550() (0x00530550)
// Process state 4 (descending). Over a cell of land type 2 or 6 (outside
// mission 7) the jumpjet stays up: a crowded cell (0x004132E0) sends it to a
// random adjacent cell (state 3), else it claims its cell (state 2, full
// height). Otherwise an unlandable target (slot 101, spot test 0x00476460;
// a unit on spot 0 always lands) stops the move; the target is claimed
// (+0x88, slot 58). The target height drops to 0; on the ground the object
// is placed at the target (on a bridge above ground: +0x79), the move ends,
// the object is redrawn and its cell claim released (state 0).
#include "shared/jumpjet_locomotion.hpp"
#include "shared/unknown_geometry.hpp"
#include "shared/cell.hpp"
#include "shared/id_source.hpp"
#include "shared/techno_type.hpp"
#include "shared/infantry.hpp"
// @ref ?unknown_coord_a6e3e0@@3UCoordStruct@@A=00a6e3e0
// @ref ?Unknown_004132E0@UnknownTracker839EA0@@QAE_NPAVFootClass@@@Z=004132e0
// @ref ?Unknown_00413310@UnknownTracker839EA0@@QAEXPAVTechnoClass@@@Z=00413310
// @ref ?unknown_tracker_839ea0@@3UUnknownTracker839EA0@@A=00839ea0
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref ?Unknown_004763D0@@YIHABUCoordStruct@@@Z=004763d0

void JumpjetLocomotionClass::unknown_530550()
{
    CellClass &cell = Map[unknown_3c];
    if ((cell.unknown_ec == 2 || cell.unknown_ec == 6) && LinkedTo->MissionQueue != 7 && LinkedTo->unknown_slot91() != 7) {
        if (unknown_tracker_839ea0.Unknown_004132E0(LinkedTo)) {
            int facing = Random_Pick(0, 7);
            CellClass *here = (CellClass *)LinkedTo->unknown_slot105();
            LinkedTo->unknown_slot260(&here->Adjacent_Cell(facing), 1);
            unknown_4c = 3;
        } else {
            ((CellClass *)LinkedTo->unknown_slot105())->Set_unknown_e0(LinkedTo);
            unknown_4c = 2;
            unknown_78 = Height;
        }
        return;
    }
    int result = LinkedTo->unknown_slot101(&cell, -1, -1, 0, 1);
    int spot = Unknown_004763D0(unknown_3c);
    bool landable;
    if (cell.unknown_476460(spot, (cell.unknown_140 >> 8) & 1) || unknown_88) {
        landable = true;
    } else {
        landable = false;
    }
    if (LinkedTo->Kind_Of() == 1 && spot == 0) {
        landable = true;
    }
    if (LinkedTo->MissionQueue != 7 && LinkedTo->unknown_slot91() != 7) {
        if (!landable || (!(Map[unknown_3c].unknown_140 & 0x100) && (result > 2 || (result == 2 && !unknown_88)))) {
            Stop_Moving();
            return;
        }
        if (!unknown_88) {
            unknown_88 = true;
            LinkedTo->unknown_slot58(unknown_3c);
        }
    }
    unknown_78 = 0;
    int height = LinkedTo->unknown_slot108();
    if (!LinkedTo->unknown_79 && (Map[Object_Coord(LinkedTo)].unknown_140 & 0x100) && height >= unknown_geometry_j) {
        height -= unknown_geometry_j;
    }
    if (height == 0) {
        LinkedTo->unknown_slot306(0);
        LinkedTo->unknown_slot71(0);
        LinkedTo->unknown_slot103(unknown_3c);
        if (Object_Coord(LinkedTo).Z > Map.Unknown_0055A280(Object_Coord(LinkedTo)) && (Map[Object_Coord(LinkedTo)].unknown_140 & 0x100)) {
            LinkedTo->unknown_79 = true;
        }
        LinkedTo->unknown_slot71(1);
        unknown_3c = unknown_coord_a6e3e0;
        unknown_48 = false;
        LinkedTo->unknown_slot93(2);
        LinkedTo->unknown_slot260(0, 1);
        if (LinkedTo->unknown_7d && !LinkedTo->unknown_76 && !LinkedTo->unknown_7a) {
            LinkedTo->unknown_slot263(0, 0, 0, 0);
            if (LinkedTo->unknown_7d) {
                LinkedTo->unknown_slot262(0, 0, 0, 0);
            }
            if (LinkedTo->unknown_7d) {
                Map.Unknown_0054A550(Object_Coord(LinkedTo), LinkedTo->unknown_1f4 - 3, LinkedTo->unknown_1f4 + 3, 0);
            }
            if (((CellClass *)LinkedTo->unknown_slot105())->unknown_e0 == LinkedTo) {
                ((CellClass *)LinkedTo->unknown_slot105())->Set_unknown_e0(0);
            }
            unknown_tracker_839ea0.Unknown_00413310(LinkedTo);
            unknown_4c = 0;
            unknown_88 = false;
        }
    }
}
