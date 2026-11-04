// bool OverlayClass::Mark(MarkType mark) (slot 71, 0x005DA970)
// TibSun overlay.cpp; the rail bridge family (0xE9..0xEC) is RA2's copy of the low bridge family.
#include "shared/overlay.hpp"
#include "shared/map_view.hpp"
#include "shared/veinhole.hpp"
#include "shared/anim.hpp"
#include "shared/rules.hpp"
#include "shared/tiberium.hpp"
#include "shared/color_scheme.hpp"
#include "shared/id_source.hpp"
#include "shared/crt_memory.hpp"

// @ref ?unknown_4718b0@CellClass@@QAE_NHHH@Z=004718b0
// @ref ?Set_Under_Bridge@CellClass@@QAEXI_N@Z=004732d0
// @ref ?Set_Under_Rail_Bridge@CellClass@@QAEXI_N@Z=00473700

// @ref _?$S41@?EA@??unknown_slot71@OverlayClass@@UAE_NH@Z@4EA=00a73120
// @ref _?_type_to_offset@?EA@??unknown_slot71@OverlayClass@@UAE_NH@Z@4PAVCell@@A=00a730a8
// @ref _?_offset_fixup@?EA@??unknown_slot71@OverlayClass@@UAE_NH@Z@4PAY02VCell@@A=00a730e0
// @ref _?_type_to_direction@?EA@??unknown_slot71@OverlayClass@@UAE_NH@Z@4PAHA=007e8a90
// @ref _?_type_to_overlay@?EA@??unknown_slot71@OverlayClass@@UAE_NH@Z@4PAHA=007e8aa0
// @ref _?_type_to_join_direction@?EA@??unknown_slot71@OverlayClass@@UAE_NH@Z@4PAHA=007e8ab0
// @ref _?_overlay_fixup@?EA@??unknown_slot71@OverlayClass@@UAE_NH@Z@4PAHA=007e8ac0
// @ref _?_direction_to_end@?EA@??unknown_slot71@OverlayClass@@UAE_NH@Z@4PAHA=007e8ac8
// @ref _?_type_to_offset2@?FM@??unknown_slot71@OverlayClass@@UAE_NH@Z@4PAVCell@@A=00a730b8
// @ref _?_offset_fixup2@?FM@??unknown_slot71@OverlayClass@@UAE_NH@Z@4PAY02VCell@@A=00a730f8
// @ref _?_type_to_direction2@?FM@??unknown_slot71@OverlayClass@@UAE_NH@Z@4PAHA=007e8ad8
// @ref _?_type_to_overlay2@?FM@??unknown_slot71@OverlayClass@@UAE_NH@Z@4PAHA=007e8ae8
// @ref _?_type_to_join_direction2@?FM@??unknown_slot71@OverlayClass@@UAE_NH@Z@4PAHA=007e8af8
// @ref _?_overlay_fixup2@?FM@??unknown_slot71@OverlayClass@@UAE_NH@Z@4PAHA=007e8b08
// @ref _?_direction_to_end2@?FM@??unknown_slot71@OverlayClass@@UAE_NH@Z@4PAHA=007e8b10

#define MAX(a,b) (((a) > (b)) ? (a) : (b))

#ifndef RA2_ADJACENT_CELL
#define RA2_ADJACENT_CELL
inline Cell Adjacent_Cell(Cell const &cell, int facing)
{
    return cell + AdjacentCell[facing & 7];
}
#endif


bool OverlayClass::unknown_slot71(int mark)
{
    int i;

    if (ObjectClass::unknown_slot71(mark)) {
        if (mark == 1 || mark == 3) {
            Cell cell = unknown_slot104();
            CellClass *cellptr = &Map[cell];

            int type = Class->ArrayIndex;

            if (cellptr->unknown_11c > 4 && type != 0xB2) {
                return false;
            }

            if (type == 0x18 || type == 0x19) {
                if (type == 0x18) {
                    cellptr->Set_Under_Bridge(0, 1);
                } else {
                    cellptr->Set_Under_Bridge(6, 1);
                }
            }

            if (type == 0xED || type == 0xEE) {
                if (type == 0xED) {
                    cellptr->Set_Under_Rail_Bridge(0, 1);
                } else {
                    cellptr->Set_Under_Rail_Bridge(6, 1);
                }
            }

            if (type == 0xA7) {
                if (VeinholeMonsterClass::Can_Spawn_At(cellptr->MapCoords)) {
                    for (int face = 0; face < 8; face++) {
                        CellClass *adj = &cellptr->Adjacent_Cell(face);
                        adj->OverlayIndex = 0xB2;
                        adj->OverlayData = 0;
                    }
                    cellptr->OverlayIndex = 0xA7;
                    cellptr->OverlayData = 0;
                    new VeinholeMonsterClass(&cellptr->MapCoords);
                }
            } else if (type == 0x7E && !unknown_a40774) {
                cellptr->unknown_47ad00();
            } else if (Class->Land == 9) {
                cellptr->OverlayIndex = Class->ArrayIndex;
                cellptr->OverlayData = 0;
            } else if (Class->Wall) {
                if (cellptr->unknown_4718b0(1, 0, 0)) {
                    cellptr->OverlayIndex = Class->ArrayIndex;
                    cellptr->OverlayData = 0;
                    cellptr->unknown_475960(true);
                    if (!unknown_a40774) {
                        Map.Unknown_0054FC60(cellptr->MapCoords);
                        Map.Unknown_00566340(cellptr->MapCoords);
                    }

                    if (unknown_placing_house_7e8a8c != -1) {
                        cellptr->unknown_50 = Map.unknown_11a8;
                    }

                    for (int face = 0; face < 8; face++) {
                        cellptr->Adjacent_Cell(face).unknown_122++;
                    }
                } else {
                    unknown_slot60();
                    return false;
                }
            } else if (Class->ArrayIndex >= 0x7A && Class->ArrayIndex <= 0x7D) {
                int index = Class->ArrayIndex - 0x7A;

                static Cell _type_to_offset[4] = {Cell(0, -1), Cell(0, -1), Cell(-1, 0), Cell(-1, 0)};
                static int _type_to_direction[4] = {4, 4, 2, 2};
                static int _type_to_overlay[4] = {92, 94, 96, 98};
                static int _type_to_join_direction[4] = {6, 2, 4, 0};
                static Cell _offset_fixup[2][3] = {
                    Cell(-1, 0), Cell(0, 0), Cell(1, 0),
                    Cell(0, -1), Cell(0, 0), Cell(0, 1)
                };
                static int _overlay_fixup[2] = {83, 74};
                static int _direction_to_end[4] = {96, 92, 98, 94};

                Cell start_cell = _type_to_offset[index] + cell;
                Cell work_cell = start_cell;
                int direction = _type_to_direction[index];
                bool clear = true;

                for (i = 0; i < 3; i++) {
                    if (Map[work_cell].OverlayIndex != -1) {
                        clear = false;
                    }
                    work_cell = Adjacent_Cell(work_cell, direction);
                }

                work_cell = start_cell;
                if (clear) {
                    for (i = 0; i < 3; i++) {
                        CellClass *cptr = &Map[work_cell];
                        cptr->OverlayIndex = _type_to_overlay[index];
                        cptr->OverlayData = i;
                        cptr->Unknown_00472540(-1);
                        work_cell = Adjacent_Cell(work_cell, direction);
                    }
                    int join_direction = _type_to_join_direction[index];
                    work_cell = Adjacent_Cell(cell, join_direction);
                    bool found_end = false;
                    int end_overlay = _direction_to_end[join_direction / 2];

                    while (Map.Unknown_0054AAB0(work_cell) && !found_end) {
                        CellClass &check_cell_class = Map[work_cell];
                        if (check_cell_class.OverlayIndex == end_overlay && check_cell_class.OverlayData == 1) {
                            found_end = true;
                        } else {
                            work_cell = Adjacent_Cell(work_cell, join_direction);
                        }
                    }
                    if (found_end) {
                        int fixup_direction = (join_direction - 4) & 7;
                        work_cell = Adjacent_Cell(work_cell, fixup_direction);
                        int length = MAX(abs(work_cell.X - start_cell.X), abs(work_cell.Y - start_cell.Y));
                        for (i = 0; i < length; i++) {
                            for (int j = 0; j < 3; j++) {
                                TPoint2D<short> sum = _offset_fixup[(fixup_direction % 4) / 2][j] + work_cell;
                                CellClass *cptr = &Map[sum];
                                cptr->OverlayIndex = _overlay_fixup[(fixup_direction % 4) / 2] + (unknown_id_source_a3d290->RandomNumber() & 0x03);
                                cptr->OverlayData = j;
                                cptr->Unknown_00472540(-1);
                            }
                            work_cell = Adjacent_Cell(work_cell, fixup_direction);
                        }
                    }
                }
            } else if (Class->ArrayIndex >= 0xE9 && Class->ArrayIndex <= 0xEC) {
                int index = Class->ArrayIndex - 0xE9;

                static Cell _type_to_offset2[4] = {Cell(0, -1), Cell(0, -1), Cell(-1, 0), Cell(-1, 0)};
                static int _type_to_direction2[4] = {4, 4, 2, 2};
                static int _type_to_overlay2[4] = {223, 225, 227, 229};
                static int _type_to_join_direction2[4] = {6, 2, 4, 0};
                static Cell _offset_fixup2[2][3] = {
                    Cell(-1, 0), Cell(0, 0), Cell(1, 0),
                    Cell(0, -1), Cell(0, 0), Cell(0, 1)
                };
                static int _overlay_fixup2[2] = {214, 205};
                static int _direction_to_end2[4] = {227, 223, 229, 225};

                Cell start_cell = _type_to_offset2[index] + cell;
                Cell work_cell = start_cell;
                int direction = _type_to_direction2[index];
                bool clear = true;

                for (i = 0; i < 3; i++) {
                    if (Map[work_cell].OverlayIndex != -1) {
                        clear = false;
                    }
                    TPoint2D<short> next = Adjacent_Cell(work_cell, direction);
                    work_cell = next;
                }

                work_cell = start_cell;
                if (clear) {
                    for (i = 0; i < 3; i++) {
                        CellClass *cptr = &Map[work_cell];
                        cptr->OverlayIndex = _type_to_overlay2[index];
                        cptr->OverlayData = i;
                        cptr->Unknown_00472540(-1);
                        work_cell = Adjacent_Cell(work_cell, direction);
                    }
                    int join_direction = _type_to_join_direction2[index];
                    work_cell = Adjacent_Cell(cell, join_direction);
                    bool found_end = false;
                    int end_overlay = _direction_to_end2[join_direction / 2];

                    while (Map.Unknown_0054AAB0(work_cell) && !found_end) {
                        CellClass &check_cell_class = Map[work_cell];
                        if (check_cell_class.OverlayIndex == end_overlay && check_cell_class.OverlayData == 1) {
                            found_end = true;
                        } else {
                            work_cell = Adjacent_Cell(work_cell, join_direction);
                        }
                    }
                    if (found_end) {
                        int fixup_direction = (join_direction - 4) & 7;
                        work_cell = Adjacent_Cell(work_cell, fixup_direction);
                        int length = MAX(abs(work_cell.X - start_cell.X), abs(work_cell.Y - start_cell.Y));
                        for (i = 0; i < length; i++) {
                            for (int j = 0; j < 3; j++) {
                                TPoint2D<short> sum = _offset_fixup2[(fixup_direction % 4) / 2][j] + work_cell;
                                CellClass *cptr = &Map[sum];
                                cptr->OverlayIndex = _overlay_fixup2[(fixup_direction % 4) / 2] + (unknown_id_source_a3d290->RandomNumber() & 0x03);
                                cptr->OverlayData = j;
                                cptr->Unknown_00472540(-1);
                            }
                            work_cell = Adjacent_Cell(work_cell, fixup_direction);
                        }
                    }
                }
            } else {
                bool clear;
                if (!unknown_a40774) {
                    if (Class == Rules->unknown_f8) {
                        clear = cellptr->unknown_478760(5, false, false, -1, 0, -1, true);
                    } else if (Class == Rules->unknown_f4 || Class == Rules->unknown_f0) {
                        clear = cellptr->unknown_478760(1, false, false, -1, 0, -1, true);
                    } else {
                        if (Class->ArrayIndex == 0x18 || Class->ArrayIndex == 0x19 ||
                                Class->ArrayIndex == 0xED || Class->ArrayIndex == 0xEE) {
                            clear = true;
                        } else {
                            if (Class->ArrayIndex == 0x66) {
                                clear = cellptr->unknown_478760(1, true, true, -1, 0, -1, true);
                                if (cellptr->unknown_11c > 4) clear = false;
                            } else {
                                clear = cellptr->unknown_478760(1, true, true, -1, 0, -1, true);
                            }
                        }
                    }
                } else {
                    clear = true;
                }

                if ((unknown_a40774 || cellptr->OverlayIndex == -1 || !OverlayTypes[cellptr->OverlayIndex]->Overrides) && clear) {

                    cellptr->OverlayIndex = Class->ArrayIndex;
                    if (type != 0x18 && type != 0x19 && type != 0xED && type != 0xEE) {
                        cellptr->OverlayData = 0;
                    }

                    if (Class->Land == 5) {
                        cellptr->OverlayData = 1;
                        cellptr->unknown_476ba0(false);
                    }

                    if (Class->Crate) {
                        cellptr->OverlayData = 0xFF;
                    }
                }

                if (Class->CellAnim != 0) {
                    CoordStruct coord = Coord;
                    coord.Z = Map.Unknown_0055A280(CoordStruct(Coord));
                    AnimClass *aptr = new AnimClass(Class->CellAnim, coord + CoordStruct(0x180, 0x180, 0), 0, 1, 0x600, 0);

                    int tibtype = cellptr->Get_Tiberium_Type();
                    if (tibtype != -1) {
                        TiberiumClass *tiberium = unknown_TiberiumClass_list_00ac0b30[tibtype];
                        if (tiberium != 0) {
                            aptr->unknown_bc = (int)ColorSchemes[tiberium->unknown_c0]->Converter;
                            aptr->unknown_e4 = cellptr->unknown_10a;
                        }
                    }
                }
            }

            cellptr->Unknown_00472540(-1);

            unknown_74 = false;
            unknown_76 = true;

            unknown_slot60();
            return true;
        }
    }
    return false;
}
