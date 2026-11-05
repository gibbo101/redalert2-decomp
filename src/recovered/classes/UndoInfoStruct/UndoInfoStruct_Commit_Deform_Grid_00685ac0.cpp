// bool __fastcall Commit_Deform_Grid_00685ac0(bool forced, Cell center) (0x00685AC0)
// Writes the deformation grid around center back to the map. Every free cell with a changed
// corner and a corner spread under 16 takes the lowest corner / 15 as its height and the ramp
// matching its corners; a smudge on it is cleared whole, its occupiers are lifted and put back,
// and the touched cells and their LAT neighbours are redrawn. Frees the grid.
#include "shared/object.hpp"
#include "shared/smudge_type.hpp"
#include "shared/tactical.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ??AMapClass@@QAEAAVCellClass@@ABVCell@@@Z=00548070
// @ref ??0?$VectorClass@PAVObjectClass@@@@QAE@HPBQAVObjectClass@@@Z=004bfbd0
// @ref ??_7?$VectorClass@PAVObjectClass@@@@6B@=0079a91c
// @ref ??_7?$DynamicVectorClass@PAVObjectClass@@@@6B@=0079db7c
// @ref ?SmudgeTypes@@3V?$DynamicVectorClass@PAVSmudgeTypeClass@@@@A=00a40bc8
// @ref ?unknown_rect_839630@@3VRect@@A=00839630
// @ref ?unknown_tactical_83996c@@3PAVTactical@@A=0083996c
// @ref ?unknown_4752b0@CellClass@@QBE?AVRect@@XZ=004752b0
// @ref ?Unknown_00472540@CellClass@@QAEXH@Z=00472540
// @ref ?unknown_47be60@CellClass@@QAEXXZ=0047be60
// @ref ?unknown_471d10@CellClass@@QAE_NXZ=00471d10
// @ref ?Unknown_0056A870@MapClass@@QAEXH@Z=0056a870
// @ref ?Unknown_00631570@RadarClass@@QAEXABVCell@@@Z=00631570
// @ref ?Register_Dirty_Area@Tactical@@QAEXVRect@@_N@Z=006a3020
// @ref ??3@YAXPAX@Z=00781d3b

extern Rect unknown_rect_839630;
extern int *unknown_ramp_corners_7f4174[19];

bool __fastcall Commit_Deform_Grid_00685ac0(bool forced, Cell center)
{
    Cell lo = center - Cell(14, 14);
    Cell hi = center + Cell(14, 14);
    lo.X = lo.X < 0 ? 0 : lo.X;
    lo.Y = lo.Y < 0 ? 0 : lo.Y;
    int width = Map.unknown_128 - Map.unknown_120;
    hi.X = width < hi.X ? width : hi.X;
    int height = Map.unknown_12c - Map.unknown_124;
    hi.Y = height < hi.Y ? height : hi.Y;
    Rect bound(0, 0, 0, 0);
    Cell least(32767, 32767);
    Cell most(0, 0);
    DynamicVectorClass<ObjectClass *> objects;
    for (int y = lo.Y; y <= hi.Y; y++) {
        for (int x = lo.X; x <= hi.X; x++) {
            CellClass *cell = &Map[Cell(x + unknown_undo_x_8286e8, y + unknown_undo_y_8286ec)];
            if (!unknown_undo_cell_free_685150(cell, forced)) continue;
            UnknownUndoCell &point1 = unknown_undo_cells_abceac[x + y * unknown_undo_width_8286e4];
            UnknownUndoCell &point2 = unknown_undo_cells_abceac[x + 1 + y * unknown_undo_width_8286e4];
            UnknownUndoCell &point3 = unknown_undo_cells_abceac[x + 1 + (y + 1) * unknown_undo_width_8286e4];
            UnknownUndoCell &point4 = unknown_undo_cells_abceac[x + (y + 1) * unknown_undo_width_8286e4];
            if (point1.unknown_05 || point2.unknown_05 || point3.unknown_05 || point4.unknown_05) {
                int heights[4];
                heights[0] = point1.Value;
                heights[1] = point2.Value;
                heights[2] = point3.Value;
                heights[3] = point4.Value;
                int lowest = 1000;
                int highest = 0;
                for (int i = 0; i < 4; i++) {
                    if (heights[i] < lowest) lowest = heights[i];
                    if (heights[i] > highest) highest = heights[i];
                }
                if (highest - lowest > 15) continue;
                objects.Clear();
                ObjectClass *object = cell->OccupierPtr;
                while (object) {
                    objects.Add(object);
                    object = object->unknown_30;
                }
                int index;
                for (index = 0; index < objects.Count(); index++) {
                    objects[index]->unknown_slot71(0);
                }
                Rect cell_bound(0, 0, 0, 0);
                cell_bound = cell->unknown_4752b0();
                int old_height = cell->unknown_11b;
                cell->unknown_11b = (char)(lowest / 15);
                Map.Unknown_0056A870(cell->unknown_11b);
                if (old_height != cell->unknown_11b) {
                    cell->unknown_47be60();
                }
                cell->Unknown_00472540(-1);
                if (cell->SmudgeIndex != -1) {
                    SmudgeTypeClass *smudge = SmudgeTypes[cell->SmudgeIndex];
                    Cell smudge_cell = cell->MapCoords;
                    smudge_cell -= Cell(cell->SmudgeData % smudge->Width, cell->SmudgeData / smudge->Width);
                    for (int row = 0; row < smudge->Height; row++) {
                        for (int column = 0; column < smudge->Width; column++) {
                            Map[smudge_cell + Cell(column, row)].SmudgeIndex = -1;
                        }
                    }
                }
                Cell current(cell->Fetch_CellID());
                Map.Unknown_00631570(current);
                if (current.X < least.X) least.X = current.X;
                if (current.X > most.X) most.X = current.X;
                if (current.Y < least.Y) least.Y = current.Y;
                if (current.Y > most.Y) most.Y = current.Y;
                for (int j = 0; j < 4; j++) {
                    heights[j] -= lowest;
                }
                for (int ramp = 0; ramp < 19; ramp++) {
                    int *corners = unknown_ramp_corners_7f4174[ramp];
                    if (corners[0] == heights[0] && corners[1] == heights[1]
                        && corners[2] == heights[2] && corners[3] == heights[3]) {
                        cell->unknown_11c = ramp;
                        if (ramp == 0) {
 cell->IsoTileIndex = unknown_tileset_a52f00;
 } else {
 cell->IsoTileIndex = ramp - 1 + unknown_tileset_a6e018;
 }
                        cell->Unknown_00472540(-1);
                        Cell id(cell->Fetch_CellID());
                        Map.Unknown_00631570(id);
                        cell_bound = Union(cell_bound, cell->unknown_4752b0());
                        if (id.X < least.X) least.X = id.X;
                        if (id.X > most.X) most.X = id.X;
                        if (id.Y < least.Y) least.Y = id.Y;
                        if (id.Y > most.Y) most.Y = id.Y;
                        break;
                    }
                }
                bound = Union(bound, cell_bound);
                for (index = 0; index < objects.Count(); index++) {
                    objects[index]->unknown_slot71(1);
                    objects[index]->unknown_slot109(0);
                }
            }
        }
    }
    delete[] unknown_undo_cells_abceac;
    unknown_undo_cells_abceac = 0;
    bound.Y -= unknown_rect_839630.Y;
    unknown_tactical_83996c->Register_Dirty_Area(bound, false);
    for (int i = least.Y - 1; i <= most.Y + 1; i++) {
        for (int j = least.X - 1; j <= most.X + 1; j++) {
            Cell id(j, i);
            CellClass *target = &Map[id];
            Rect lat_rect = target->unknown_4752b0();
            if (target->unknown_471d10()) {
                lat_rect = Union(lat_rect, target->unknown_4752b0());
                lat_rect = lat_rect - unknown_rect_839630.Top_Left();
                if (lat_rect.Is_Valid()) {
                    unknown_tactical_83996c->Register_Dirty_Area(lat_rect, false);
                }
            }
        }
    }
    return true;
}
