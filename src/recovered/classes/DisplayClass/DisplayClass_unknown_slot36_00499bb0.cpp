// bool DisplayClass::unknown_slot36(Cell const &cell, HouseClass *house) (0x00499BB0, slot 36)
// Maps a cell and spreads the reveal (hypothesis: Westwood's Map_Cell): marks
// it mapped and visible (+0x140 bit 1, +0x12C bit 3), takes the tactical
// view's shroud frames of both layers and has the view redraw it when they
// changed. Then for each layer and each adjacent cell not yet fully shrouded
// in that layer: a neighbour the view now shows fully shrouded is marked so
// (+0x12C bit 4 / +0x140 bit 0) and its own neighbours' frames refreshed, or
// mapped in turn when it is not yet mapped; other neighbours take their new
// frame. When the cell changed the map redraws it (0x00568520, as slot 37).
// True when it changed.
#include "shared/display.hpp"
#include "shared/map_cell.hpp"
#include "shared/tactical.hpp"
#include "shared/id_source.hpp"
#include "shared/map_view.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ??AMapClass@@QAEAAVCellClass@@ABVCell@@@Z=00548070
// @ref ?unknown_tactical_83996c@@3PAVTactical@@A=0083996c
// @ref ?Cell_Shadow@Tactical@@QAEHABVCell@@_N@Z=006a8d40
// @ref ?Unknown_006AADD0@Tactical@@QAEXPAVCellClass@@@Z=006aadd0
// @ref ?Unknown_00568520@MapClass@@QAEXPAVCellClass@@PAVHouseClass@@_N@Z=00568520
// @ref ?unknown_47be00@CellClass@@QAEXXZ=0047be00
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref ?AdjacentCell@@3QBVCell@@B=00851a70

bool DisplayClass::unknown_slot36(Cell const &cell, HouseClass *house)
{
    CellClass &target = (*this)[cell];
    bool unmapped = !(target.unknown_140 & 2);
    bool changed = !(target.unknown_140 & 2) || !(target.unknown_12c & 8);
    bool mapped = changed;
    target.unknown_140 = (target.unknown_140 & ~0x40) | 2;
    target.unknown_12c |= 8;
    unsigned char frame = unknown_tactical_83996c->Cell_Shadow(cell, 0);
    if (frame != target.unknown_120) {
        changed = true;
        target.unknown_120 = frame;
    }
    if (target.unknown_120 == 0xFF) {
        target.unknown_12c |= 0x10;
    }
    frame = unknown_tactical_83996c->Cell_Shadow(cell, 1);
    if (frame != target.unknown_121) {
        changed = true;
        target.unknown_121 = frame;
    }
    if (target.unknown_121 == 0xFF) {
        target.unknown_140 |= 1;
    }
    if (changed) {
        unknown_tactical_83996c->Unknown_006AADD0(&target);
    }

    for (int facing = 0; facing < 8; facing++) {
        Cell adjacent = AdjacentCell[facing & 7] + cell;
        CellClass &near_cell = (*this)[adjacent];

        if (adjacent != cell && !(near_cell.unknown_12c & 0x10)) {
            int shade = unknown_tactical_83996c->Cell_Shadow(adjacent, 0);
            if (shade == -1) {
                if (!(near_cell.unknown_12c & 8)) {
                    unknown_slot36(adjacent, house);
                } else {
                    near_cell.unknown_12c |= 0x10;
                    unknown_tactical_83996c->Unknown_006AADD0(&near_cell);
                    for (int around = 0; around < 8; around++) {
                        Cell next = AdjacentCell[around & 7] + adjacent;
                        CellClass &next_cell = (*this)[next];
                        unsigned char next_frame = unknown_tactical_83996c->Cell_Shadow(next, 0);
                        if (next_frame != next_cell.unknown_120) {
                            next_cell.unknown_120 = next_frame;
                            unknown_tactical_83996c->Unknown_006AADD0(&next_cell);
                        }
                    }
                }
            } else if (shade != -2 && !(near_cell.unknown_12c & 8)) {
                unknown_slot36(adjacent, house);
            } else if (shade >= 0 && shade != (char)near_cell.unknown_120) {
                near_cell.unknown_120 = shade;
                unknown_tactical_83996c->Unknown_006AADD0(&near_cell);
            }
        }

        if (adjacent != cell && !(near_cell.unknown_140 & 1)) {
            int shade = unknown_tactical_83996c->Cell_Shadow(adjacent, 1);
            if (shade == -1) {
                if (!(near_cell.unknown_140 & 2)) {
                    unknown_slot36(adjacent, house);
                } else {
                    near_cell.unknown_140 |= 1;
                    unknown_tactical_83996c->Unknown_006AADD0(&near_cell);
                    for (int around = 0; around < 8; around++) {
                        Cell next = AdjacentCell[around & 7] + adjacent;
                        CellClass &next_cell = (*this)[next];
                        unsigned char next_frame = unknown_tactical_83996c->Cell_Shadow(next, 1);
                        if (next_frame != next_cell.unknown_121) {
                            next_cell.unknown_121 = next_frame;
                            unknown_tactical_83996c->Unknown_006AADD0(&next_cell);
                        }
                    }
                }
            } else if (shade != -2 && !(near_cell.unknown_140 & 2)) {
                unknown_slot36(adjacent, house);
            } else if (shade >= 0 && shade != (char)near_cell.unknown_121) {
                near_cell.unknown_121 = shade;
                unknown_tactical_83996c->Unknown_006AADD0(&near_cell);
            }
        }
    }

    if (changed) {
        Map.Unknown_00568520(&target, house, mapped);
    }
    if ((target.unknown_140 & 2) && unmapped && (unknown_id_source_a3d290->unknown_000 & 0x1000)) {
        target.unknown_47be00();
    }
    return changed;
}
