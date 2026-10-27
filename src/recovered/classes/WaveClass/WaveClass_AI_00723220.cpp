// void WaveClass::AI() (0x00723220)
// A type 0 wave steps through its cells, types 1 and 2 fade.
#include "shared/wave.hpp"
#include "shared/cell.hpp"
// @ref ?AI@ObjectClass@@UAEXXZ=005d27f0
// @ref ?Update_Wave_00724200@WaveClass@@QAEXXZ=00724200
// @ref ?Damage_Cell_00721eb0@WaveClass@@QAEXABUCoordStruct@@@Z=00721eb0
// @ref ?unknown_475d60@CellClass@@QBE?AUCoordStruct@@XZ=00475d60

void WaveClass::AI()
{
    switch (Type) {
    case 0:
        unknown_func_7232d0();
        break;
    case 1:
    case 2:
        unknown_func_723340();
        break;
    }
}
