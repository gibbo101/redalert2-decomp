#include "shared/veinhole.hpp"
#include "shared/map_cell_view.hpp"
#include "shared/random.hpp"
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref ??RRandom2Class@@QAEHXZ=00638840
// @ref ?unknown_cells_428ac0@@YIHXZ=00428ac0
// @ref ?unknown_veinhole_buffer_ad07a0@@3PAEA=00ad07a0
// @ref ?unknown_cell_index_428a90@@YIHABVCell@@@Z=00428a90
// @ref ?unknown_47a7a0@CellClass@@QAEXXZ=0047a7a0
// @ref ?Sift_Down@UnknownVeinHeap@@QAEXH@Z=0058f090
// @ref ??_C@_0BJ@EOJK@Exiting?5Remove_Matching?6?$AA@=007f96e4

void VeinholeMonsterClass::unknown_func_712300(CellClass *cellptr)
{
    if (cellptr->OverlayIndex == 0x7e && cellptr->OverlayData >= 0x30) {

        bool facingbools[4];
        int facing;
        for (facing = 0; facing < 8; facing += 2) {
            CellClass *adjacent = &cellptr->Adjacent_Cell(facing);
            facingbools[facing / 2] = (adjacent->OverlayIndex == 0x7e && (adjacent->OverlayData < 0x30 || adjacent->OverlayData > 0x30 + 3));
        }

        cellptr->unknown_47a7a0();
        unknown_ec--;

        for (facing = 0; facing < 8; facing += 2) {
            CellClass *adjacent = &cellptr->Adjacent_Cell(facing);
            if (adjacent->OverlayIndex == -1) {
                int cindex = unknown_cell_index_428a90(adjacent->MapCoords);
                if (cindex >= 0 && cindex < unknown_cells_428ac0()) {
                    unknown_b0[cindex] = false;
                    unknown_veinhole_buffer_ad07a0[cindex] = false;
                }

                if (facingbools[facing / 2] == true && !unknown_e8) {
                    unknown_9c->Remove_Matching(UnknownVeinNode(adjacent->MapCoords));
                }
            }
        }

        int overlay = cellptr->OverlayIndex;
        ::Cell &cell = cellptr->MapCoords;
        int cindex = unknown_cell_index_428a90(cell);
        if (cindex >= 0 && cindex < unknown_cells_428ac0()) {
            if (overlay == -1) {
                unknown_b0[cindex] = false;
                unknown_veinhole_buffer_ad07a0[cindex] = false;
            } else if (!unknown_e8) {
                if (unknown_98 < Rules->unknown_d4) {
                    unknown_a0[unknown_98].Position = cell;
                    unknown_a0[unknown_98].Key = float(Frame / 50 + abs(unknown_id_source_a3d290->Random()() % 50) + 1);
                    unknown_9c->Insert(&unknown_a0[unknown_98++]);
                    unknown_b0[cindex] = true;
                    unknown_veinhole_buffer_ad07a0[cindex] = true;
                }
            }
        }
    }
}
