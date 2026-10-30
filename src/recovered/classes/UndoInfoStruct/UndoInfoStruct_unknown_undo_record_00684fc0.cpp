// void __fastcall unknown_undo_record_684fc0(Point2D const &cell, int value) (0x00684FC0)
// Appends (cell X, cell Y, value) to the unit's undo list (0x00ABCE18).
// UndoInfoStruct (shared/vector_elements.hpp) and the list are defined by this unit's first source
// (HeaderStatics_diagonal_init_00684d50.cpp).
#include "shared/rect.hpp"
// @ref ?unknown_UndoInfoStruct_list_00abce18@@3V?$DynamicVectorClass@UUndoInfoStruct@@@@A=00abce18

void __fastcall unknown_undo_record_684fc0(Point2D const &cell, int value)
{
    UndoInfoStruct info;
    info.X = cell.X;
    info.Y = cell.Y;
    info.Value = value;
    unknown_UndoInfoStruct_list_00abce18.Add(info);
}
