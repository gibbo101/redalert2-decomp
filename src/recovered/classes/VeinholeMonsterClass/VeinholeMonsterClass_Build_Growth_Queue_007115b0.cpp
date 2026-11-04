// @ref ??0?$VectorClass@VCell@@@@QAE@IPBVCell@@@Z=0042d4a0
// @ref ??8?$VectorClass@VCell@@@@UBE_NABV0@@Z=0042ce10
// @ref ??_7?$DynamicVectorClass@VCell@@@@6B@=0079c5a0
// @ref ??_7?$VectorClass@VCell@@@@6B@=0079c5e0
// @ref ??_E?$DynamicVectorClass@VCell@@@@UAEPAXI@Z=0042d3e0
// @ref ??_E?$VectorClass@VCell@@@@UAEPAXI@Z=0042d390
// @ref ??_G?$DynamicVectorClass@VCell@@@@UAEPAXI@Z=0042d3e0
// @ref ??_G?$VectorClass@VCell@@@@UAEPAXI@Z=0042d390
// @ref ?Clear@?$DynamicVectorClass@VCell@@@@UAEXXZ=0042cc10
// @ref ?Clear@?$VectorClass@VCell@@@@UAEXXZ=0042cfb0
// @ref ?Fetch@?$VectorClass@VCell@@@@UBE?AVCell@@H@Z=0042cc60
// @ref ?ID@?$DynamicVectorClass@VCell@@@@UAEHABVCell@@@Z=0042d120
// @ref ?ID@?$DynamicVectorClass@VCell@@@@UAEHPBVCell@@@Z=0042cc40
// @ref ?ID@?$VectorClass@VCell@@@@UAEHABVCell@@@Z=0042cfe0
// @ref ?ID@?$VectorClass@VCell@@@@UAEHPBVCell@@@Z=0042d030
// @ref ?Resize@?$DynamicVectorClass@VCell@@@@UAE_NHPBVCell@@@Z=0042d050
// @ref ?Resize@?$VectorClass@VCell@@@@UAE_NHPBVCell@@@Z=0042cee0
// Veinhole growth traversal, independently bounded at007115B0.
#include "shared/veinhole.hpp"
#include "shared/map_cell_view.hpp"
#include "shared/map_view.hpp"
// @ref ?unknown_cells_428ac0@@YIHXZ=00428ac0
// @ref ?unknown_cell_index_428a90@@YIHABVCell@@@Z=00428a90
void VeinholeMonsterClass::unknown_func_7115b0()
{
    DynamicVectorClass<::Cell> pending;
    pending.Set_Growth_Step(5000);
    unknown_98=0;
    unknown_ec=0;
    unknown_9c->Clear();
    for (int index=unknown_cells_428ac0()-1; index>=0; --index) unknown_b0[index]=0;
    int row_or_facing;
    for (row_or_facing=-2; row_or_facing<=2; ++row_or_facing) {
        for (int column=-2; column<=2; ++column) {
            CellClass *cell=&Map[::Cell(column,row_or_facing)+Cell];
            if (cell->OverlayIndex==0x7e) {
                int index=unknown_cell_index_428a90(cell->MapCoords);
                pending.Add(::Cell(column,row_or_facing)+Cell);
                if (index>=0 && index<unknown_cells_428ac0()) {
                    unknown_veinhole_buffer_ad07a0[index]=1;
                    unknown_b0[index]=1;
                    cell->unknown_140|=0x8000;
                    if (cell->OverlayData>=0x30 && cell->OverlayData<=0x33) {
                        ++unknown_ec;
                    } else if (unknown_98<Rules_Vein_Node_Count()) {
                        unknown_a0[unknown_98].Position=cell->MapCoords;
                        unknown_a0[unknown_98].Key=0;
                        unknown_9c->Insert(&unknown_a0[unknown_98++]);
                    }
                }
            }
        }
    }
    while (pending.Count()>0) {
        int last=pending.Count()-1;
        CellClass *cell=&Map[pending[last]];
        pending.Delete(last);
        for (row_or_facing=0; row_or_facing<8; ++row_or_facing) {
            CellClass *adjacent=&cell->Adjacent_Cell(row_or_facing);
            int index=unknown_cell_index_428a90(adjacent->MapCoords);
            if (adjacent->OverlayIndex==0x7e && !(adjacent->unknown_140&0x8000)) {
                if ((adjacent->OverlayData>=0x30 && adjacent->OverlayData<0x35) || !adjacent->unknown_47a670()) {
                    pending.Add(adjacent->MapCoords);
                    ++unknown_ec;
                } else if (unknown_98<Rules_Vein_Node_Count()) {
                    unknown_a0[unknown_98].Position=adjacent->MapCoords;
                    unknown_a0[unknown_98].Key=0;
                    unknown_9c->Insert(&unknown_a0[unknown_98++]);
                    if (adjacent->OverlayData>=0x30) pending.Add(adjacent->MapCoords);
                }
                adjacent->unknown_140|=0x8000;
                if (index>=0 && index<unknown_cells_428ac0()) {
                    unknown_veinhole_buffer_ad07a0[index]=1;
                    unknown_b0[index]=1;
                }
                ++unknown_ec;
            }
        }
    }
}
