// static void OverlayClass::unknown_func_5dc180() (0x005DC180)
// Removes overlay 0x7E from every cell, remembering the cells whose
// overlay data was at least 0x30, then runs the 0x0047A670 / 0x0047AD00
// pair on those cells in reverse order.
// Assumptions: the map iterator names (0x0055A550 reset, 0x0055A490 next).
#include "shared/overlay.hpp"
// @ref ??_7?$VectorClass@PAVCellClass@@@@6B@=007a59b8
// @ref ??_E?$VectorClass@PAVCellClass@@@@UAEPAXI@Z=0056ae40
// @ref ??_G?$VectorClass@PAVCellClass@@@@UAEPAXI@Z=0056ae40
// @ref ??8?$VectorClass@PAVCellClass@@@@UBE_NABV0@@Z=0056ba80
// @ref ?Resize@?$VectorClass@PAVCellClass@@@@UAE_NHPBQAVCellClass@@@Z=0056bac0
// @ref ?Clear@?$VectorClass@PAVCellClass@@@@UAEXXZ=0056bb70
// @ref ?ID@?$VectorClass@PAVCellClass@@@@UAEHABQAVCellClass@@@Z=0056bba0
// @ref ?ID@?$VectorClass@PAVCellClass@@@@UAEHPBQAVCellClass@@@Z=0056bbe0
// @ref ?Fetch@?$VectorClass@PAVCellClass@@@@UBEPAVCellClass@@H@Z=0056acd0
// @ref ??_7?$DynamicVectorClass@PAVCellClass@@@@6B@=007a5efc
// @ref ??_E?$DynamicVectorClass@PAVCellClass@@@@UAEPAXI@Z=0058ede0
// @ref ??_G?$DynamicVectorClass@PAVCellClass@@@@UAEPAXI@Z=0058ede0
// @ref ?Resize@?$DynamicVectorClass@PAVCellClass@@@@UAE_NHPBQAVCellClass@@@Z=0058e880
// @ref ?Clear@?$DynamicVectorClass@PAVCellClass@@@@UAEXXZ=0058de10
// @ref ?ID@?$DynamicVectorClass@PAVCellClass@@@@UAEHABQAVCellClass@@@Z=0058e930
// @ref ?ID@?$DynamicVectorClass@PAVCellClass@@@@UAEHPBQAVCellClass@@@Z=0058de40
#include "shared/map_view.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Unknown_0055A550@MapClass@@QAEXXZ=0055a550
// @ref ?Unknown_0055A490@MapClass@@QAEPAVCellClass@@XZ=0055a490
// @ref ?unknown_47a670@CellClass@@QBE_NXZ=0047a670
// @ref ?unknown_47ad00@CellClass@@QAEXXZ=0047ad00
// @ref ??3@YAXPAX@Z=00781d3b

void OverlayClass::unknown_func_5dc180()
{
    Map.Unknown_0055A550();
    CellClass *cell = Map.Unknown_0055A490();
    DynamicVectorClass<CellClass *> cells;
    cells.Set_Growth_Step(1000);
    while (cell != 0) {
        if (cell->OverlayIndex == 0x7E) {
            if (cell->OverlayData >= 0x30) {
                cells.Add(cell);
            }
            cell->OverlayIndex = -1;
            cell->OverlayData = 0;
        }
        cell = Map.Unknown_0055A490();
    }
    for (int index = cells.Count() - 1; index >= 0; index--) {
        CellClass *dense = cells[index];
        if (dense->unknown_47a670()) {
            dense->unknown_47ad00();
        }
    }
}
