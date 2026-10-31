// Fresh unowned operation; entryECX overwritten. Source ownership/name remain hypotheses.
#include "shared/map_region.hpp"
#include "shared/map_view.hpp"
#include "shared/cell.hpp"
// Physical ECX CellClasspointer/AL0or1/plainRET; nominal free/member/bool intent are hypotheses.
bool __fastcall Unknown_Cell_Predicate_0047b5e0(CellClass *cell);
// @ref ?Unknown_Cell_Predicate_0047b5e0@@=0047b5e0
bool __fastcall Generation_Cell_In_Bounds_0058da10(Cell const &position);
void Mark_Adjacent_Grid_Weights_00584bd0()
{
    Map.Unknown_0055A550();
    CellClass *current=Map.Unknown_0055A490();
    while(current!=0) {
        if(current->unknown_47b7c0()) {
            for(int direction=0;direction<8;++direction) {
                Cell position=current->MapCoords;
                Cell next=unknown_adjacent_851a70[direction&7]+position;
                if(Generation_Cell_In_Bounds_0058da10(next) && Map[next].unknown_47b590()) {
                    int at=(int)((unsigned int)(int)next.Y*(unsigned int)unknown_map_cell_side_84e804+(unsigned int)(int)next.X);
                    unknown_map_cells_a70a24[at].unknown_08=0.5;
                    at=(int)((unsigned int)(int)next.Y*(unsigned int)unknown_map_cell_side_84e804+(unsigned int)(int)next.X);
                    unknown_map_cells_a70a24[at].unknown_45[0]=1;
                    break;
                }
            }
        } else if(Unknown_Cell_Predicate_0047b5e0(current)) {
            for(int direction=0;direction<8;++direction) {
                Cell position=current->MapCoords;
                Cell next=unknown_adjacent_851a70[direction&7]+position;
                if(Generation_Cell_In_Bounds_0058da10(next) && Map[next].unknown_47b590()) {
                    int at=(int)((unsigned int)(int)next.Y*(unsigned int)unknown_map_cell_side_84e804+(unsigned int)(int)next.X);
                    unknown_map_cells_a70a24[at].unknown_45[0]=1;
                    break;
                }
            }
        }
        current=Map.Unknown_0055A490();
    }
}
