// static void VeinholeMonsterClass::unknown_func_711280(bool rebuild) (0x00711280)
// With rebuild, frees every monster's buffers and the shared table and
// allocates them again (nodes, heap and per-cell table); then clears the
// shared table and the cells' vein bit (0x8000), lets every monster mark its
// cells again (placed ones 0x00711AA0, others 0x007115B0) and removes vein
// overlays (0x7E) no monster covers.
#include "shared/veinhole.hpp"
#include "shared/map_cell_view.hpp"
#include "shared/crt_memory.hpp"
// @ref ?unknown_cells_428ac0@@YIHXZ=00428ac0
// @ref ?unknown_veinhole_buffer_ad07a0@@3PAEA=00ad07a0
// @ref ?unknown_cell_index_428a90@@YIHABVCell@@@Z=00428a90
// @ref ?unknown_func_711c90@VeinholeMonsterClass@@QAEXXZ=00711c90
// @ref ?unknown_func_711aa0@VeinholeMonsterClass@@QAEXXZ=00711aa0
// @ref ?unknown_func_7115b0@VeinholeMonsterClass@@QAEXXZ=007115b0

void __fastcall VeinholeMonsterClass::unknown_func_711280(bool rebuild)
{
    int cells = unknown_cells_428ac0();
    int index;
    if (rebuild) {
        for (index = Array.Count() - 1; index >= 0; index--) {
            Array[index]->unknown_func_711c90();
        }
        if (unknown_veinhole_buffer_ad07a0 != 0) {
            delete [] unknown_veinhole_buffer_ad07a0;
            unknown_veinhole_buffer_ad07a0 = 0;
        }
        for (index = Array.Count() - 1; index >= 0; index--) {
            Array[index]->unknown_a0 = new UnknownVeinNode[Rules_Vein_Node_Count()];
            Array[index]->unknown_9c = new UnknownVeinHeap(Rules_Vein_Node_Count());
            Array[index]->unknown_b0 = new unsigned char[cells];
            memset(Array[index]->unknown_b0, 0, cells);
            Array[index]->unknown_9c->Clear();
        }
    }
    if (unknown_veinhole_buffer_ad07a0 == 0) {
        unknown_veinhole_buffer_ad07a0 = new unsigned char[cells];
    }
    Map.Unknown_0055A550();
    for (CellClass *cell = Map.Unknown_0055A490(); cell != 0; cell = Map.Unknown_0055A490()) {
        cell->unknown_140 &= ~0x8000;
    }
    memset(unknown_veinhole_buffer_ad07a0, 0, cells);
    for (index = Array.Count() - 1; index >= 0; index--) {
        if (Array[index]->unknown_e8) {
            Array[index]->unknown_func_711aa0();
        } else {
            Array[index]->unknown_func_7115b0();
        }
    }
    Map.Unknown_0055A550();
    for (cell = Map.Unknown_0055A490(); cell != 0; cell = Map.Unknown_0055A490()) {
        if (cell->OverlayIndex == 0x7e && unknown_veinhole_buffer_ad07a0[unknown_cell_index_428a90(cell->MapCoords)] == 0) {
            cell->OverlayIndex = -1;
        }
        cell->unknown_140 &= ~0x8000;
    }
}
