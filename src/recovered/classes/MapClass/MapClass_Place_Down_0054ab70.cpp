// void MapClass::Unknown_0054AB70(Cell const &cell, ObjectClass *object) (0x0054AB70)
// TibSun MapClass::Pick_Up: the object leaves the cells of its occupy list (each cell
// unlinks it, 0x00473D20, and recalculates, 0x00472540). RA2 adds: a building whose
// type hides the cells behind it (CanHideThings) gives back the OccupyHeight - 1 cells
// up and left of each foundation cell (each counted once) and its AddOccupy cells
// (the cell's +0x100 hide count).
#include "shared/map.hpp"
#include "shared/map_cell.hpp"
#include "shared/map_techno.hpp"
// @ref ?unknown_dummy_cell_a6f9f8@@3VCellClass@@A=00a6f9f8
// @ref ?unknown_473b30@CellClass@@QAEXPAVObjectClass@@_N@Z=00473b30
// @ref ?Unknown_00472540@CellClass@@QAEXH@Z=00472540
// @ref ?Copy_Cell_List_00482e10@@YIXPBVCell@@HPAV1@@Z=00482e10

void __fastcall Copy_Cell_List_00482e10(Cell const *input, int capacity, Cell *output);

void MapClass::Unknown_0054AB70(Cell const &cell, ObjectClass *object)
{
    if (!object) return;

    if (object->Class_Of()->unknown_205 && object->unknown_slot29() == 2) {
        Cell xlist[32];
        Copy_Cell_List_00482e10(object->unknown_slot64(0), 32, xlist);
        Cell const *list = xlist;
        while (list->X != 0x7FFF || list->Y != 0x7FFF) {
            Cell newcell = cell + *list;
            if (Has_Cell(newcell)) {
                (*this)[newcell].unknown_473b30(object, object->unknown_79);
                (*this)[newcell].Unknown_00472540(-1);
            }
            list++;
        }

        if (object->Kind_Of() == 6) {
            BuildingClass *building = object->Kind_Of() == 6 ? (BuildingClass *)object : 0;
            if (building->Type->CanHideThings) {
                int height = building->Type->OccupyHeight - 1;
                if (height <= 0) height = 1;
                bool seen[0x800];
                memset(seen, 0, sizeof(seen));
                for (list = xlist; list->X != 0x7FFF || list->Y != 0x7FFF; list++) {
                    Cell newcell = cell + *list;
                    Cell pos = newcell;
                    int x = list->X;
                    int y = list->Y;
                    for (int i = 0; i < height; i++) {
                        if (pos.X >= 0 && pos.Y >= 0) {
                            if (x < 0) x += 16;
                            if (y < 0) y += 16;
                            if (!seen[y * 16 + x]) {
                                seen[y * 16 + x] = true;
                                if (Has_Cell(pos)) {
                                    CellClass &cellptr = (*this)[pos];
                                    cellptr.unknown_100++;
                                }
                            }
                            pos.X--;
                            pos.Y--;
                            x--;
                            y--;
                        }
                    }
                }
                for (int index = 0; index < 8; index++) {
                    if (Is_Occupy_Offset(building->Type->AddOccupy[index])) {
                        Cell newcell = cell;
                        newcell.X += building->Type->AddOccupy[index].X;
                        newcell.Y += building->Type->AddOccupy[index].Y;
                        if (Has_Cell(newcell)) {
                            CellClass &cellptr = (*this)[newcell];
                            cellptr.unknown_100++;
                        }
                    }
                    if (Is_Occupy_Offset(building->Type->RemoveOccupy[index])) {
                        Cell newcell = cell;
                        newcell.X += building->Type->RemoveOccupy[index].X;
                        newcell.Y += building->Type->RemoveOccupy[index].Y;
                        if (Has_Cell(newcell)) {
                            CellClass &cellptr = (*this)[newcell];
                            if (cellptr.unknown_100) cellptr.unknown_100--;
                        }
                    }
                }
            }
        }
    }
}
