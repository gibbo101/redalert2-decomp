// void __fastcall TiberiumClass::Clear_Spread_Cell(Cell const &cell) (0x006E9D90)
// Marks the cell as no longer queued for spread in every tiberium type.
#include "shared/tiberium.hpp"
#include "shared/veinhole.hpp"
// @ref ?unknown_cell_index_428a90@@YIHABVCell@@@Z=00428a90

void __fastcall TiberiumClass::Clear_Spread_Cell(Cell const &cell)
{
    int index = unknown_cell_index_428a90(cell);
    for (int type = 0; type < unknown_TiberiumClass_list_00ac0b30.Count(); type++) {
        unknown_TiberiumClass_list_00ac0b30[type]->SpreadMap[index] = false;
    }
}
