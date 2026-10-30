// int CellClass::unknown_476ba0(bool pregame) (0x00476BA0)
// Westwood's CellClass::Tiberium_Adjust: an ore overlay takes the stage its
// neighbours of the same tiberium give it (from the table at 0x007D2C10; with
// pregame, a random image of the tiberium first); answers the cell's value.
#include "shared/cell.hpp"
#include "shared/overlay.hpp"
#include "shared/tiberium.hpp"
#include "shared/id_source.hpp"
// @ref ?unknown_tiberium_stage_7d2c10@@3PAHA=007d2c10

int CellClass::unknown_476ba0(bool pregame)
{
    if (OverlayIndex != -1) {
        int tiberium = OverlayClass::To_Tiberium(OverlayIndex);
        if (tiberium != -1) {
            int count = 0;
            int value = unknown_TiberiumClass_list_00ac0b30[tiberium]->Value;
            if (pregame) {
                TiberiumClass *type = unknown_TiberiumClass_list_00ac0b30[tiberium];
                OverlayIndex = (int)Random_Pick(type->Image, type->Image + type->NumFrames - 1);
            }
            for (int facing = 0; facing < 8; facing++) {
                CellClass &cell = Adjacent_Cell(facing);
                if (OverlayClass::To_Tiberium(cell.OverlayIndex) == tiberium) {
                    count++;
                }
            }
            OverlayData = unknown_tiberium_stage_7d2c10[count % unknown_TiberiumClass_list_00ac0b30[tiberium]->unknown_e4];
            return (OverlayData + 1) * value;
        }
    }
    return 0;
}
