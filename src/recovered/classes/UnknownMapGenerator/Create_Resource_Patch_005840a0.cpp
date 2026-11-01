// @ref __real@8@3fe2c0000000c0000000=007a5fd0
#include "shared/unknown_map_generator.hpp"
#include "shared/map_region.hpp"
#include "shared/map_view.hpp"
#include "shared/cell.hpp"
#include "shared/vein_heap_core.hpp"
#include "shared/isometric_tile_type.hpp"
#include "shared/terrain.hpp"
extern "C" int __cdecl sprintf(char *,char const *,...);
extern "C" char const unknown_resource_tree_format_7e1b48[];
// @ref _unknown_resource_tree_format_7e1b48=007e1b48
unsigned __fastcall Map_Random_Range_005797a0(unsigned,unsigned);
double __stdcall Randomized_Cell_Distance_005846b0(Cell const &,Cell const &);
// @ref ?Randomized_Cell_Distance_005846b0@@=005846b0
// Original resets marker to zero while current can still alias nodes[0].
// Read current->Position anew for every neighbor; do not cache that coordinate.
void UnknownMapGenerator::Create_Resource_Patch_005840a0(Cell const &position,int amount,int patchId,bool special)
{
    int marker=0;
    int capacity=(int)((unsigned)amount*10u);
    UnknownVeinNode *nodes=new UnknownVeinNode[capacity];
    UnknownVeinHeap *queue=new UnknownVeinHeap(capacity);
    bool resetForSpread=false;
    Cell spreadOrigin=position;
    int placed=0;
    int attempts=0;
    int overlayBase=special?27:102;
    queue->Clear();
    UnknownVeinNode *current=0;
    while(placed<amount) {
        if(attempts>=10)break;
        if(current==0) {
            queue->Clear();
            Map.Unknown_0055A550();
            for(CellClass *cell=Map.Unknown_0055A490();cell;cell=Map.Unknown_0055A490()) {
                Cell cellPosition=cell->MapCoords;
                unknown_map_cells_a70a24[cellPosition.Y*unknown_map_cell_side_84e804+cellPosition.X].unknown_3c=0;
            }
            marker=1;
            float &seedScore=nodes[0].Key;
            nodes[0].Position=position;
            seedScore=0.0f;
            unknown_map_cells_a70a24[position.Y*unknown_map_cell_side_84e804+position.X].unknown_3c=patchId;
            queue->Insert(nodes);
            current=queue->Remove_Min();
            resetForSpread=false;
            ++attempts;
            spreadOrigin=position;
        }
        CellClass &cell=Map[current->Position];
        if(unknown_map_cells_a70a24[current->Position.Y*unknown_map_cell_side_84e804+current->Position.X].unknown_45[0]==0) {
            if(!resetForSpread) {
                resetForSpread=true;
                spreadOrigin=current->Position;
                queue->Clear();
                marker=0;
                if(!special) {
                    char treeName[20];
                    int variant=(int)Map_Random_Range_005797a0(1,3);
                    sprintf(treeName,unknown_resource_tree_format_7e1b48,variant%10);
                    new TerrainClass(TerrainTypes[TerrainTypeClass::From_Name(treeName)],spreadOrigin);
                }
            }
            if(cell.OverlayIndex==-1) {
                cell.OverlayIndex=Map_Random_Range_005797a0(0,11)+overlayBase;
                ++placed;
            } else if(cell.OverlayData<11) {
                ++cell.OverlayData;
                ++placed;
            }
        }
        UnknownVeinNode *next=&nodes[marker];
        for(int facing=0;facing<8;++facing) {
            Cell adjacent=current->Position + unknown_adjacent_851a70[facing&7];
            if(Map.Unknown_0055A660(adjacent,true)) {
                CellClass &neighbor=Map[adjacent];
                if(neighbor.unknown_47b590() &&
                   ((neighbor.OverlayIndex==-1 && unknown_map_cells_a70a24[adjacent.Y*unknown_map_cell_side_84e804+adjacent.X].unknown_3c!=patchId) ||
                    (neighbor.OverlayData<11 && neighbor.Get_Tiberium_Type()!=-1))) {
                    next->Position=adjacent;
                    next->Key=(float)Randomized_Cell_Distance_005846b0(spreadOrigin,adjacent);
                    unknown_map_cells_a70a24[adjacent.Y*unknown_map_cell_side_84e804+adjacent.X].unknown_3c=patchId;
                    ++marker;
                    queue->Insert(next++);
                }
            }
        }
        current=queue->Remove_Min();
    }
    delete[] nodes;
    delete queue;
}
