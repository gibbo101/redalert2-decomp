// void WaveClass::unknown_func_7232d0() (0x007232D0; expanded into AI, also kept out of line)
// Type 0 step: runs the cell animation, then the base AI or the end.
#include "shared/wave.hpp"
#include "shared/cell.hpp"
// @ref ?AI@ObjectClass@@UAEXXZ=005d27f0
// @ref ?Update_Wave_00724200@WaveClass@@QAEXXZ=00724200
// @ref ?Damage_Cell_00721eb0@WaveClass@@QAEXABUCoordStruct@@@Z=00721eb0
// @ref ?unknown_475d60@CellClass@@QBE?AUCoordStruct@@XZ=00475d60

void WaveClass::unknown_func_7232d0()
{
    Update_Wave_00724200();
    for (int index = 0; index < Cells.Count(); index++) {
        Damage_Cell_00721eb0(Cells[index]->unknown_475d60());
    }
    if (--unknown_11c < 0) {
        unknown_slot60();
    } else {
        ObjectClass::AI();
    }
}
