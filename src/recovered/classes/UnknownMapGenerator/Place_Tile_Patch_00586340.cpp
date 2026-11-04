#include "shared/unknown_map_generator.hpp"
#include "shared/map_region.hpp"
#include "shared/map_view.hpp"
#include "shared/cell.hpp"
#include "shared/vein_heap_core.hpp"
bool __fastcall Generation_Cell_In_Bounds_0058da10(Cell const &);
double __stdcall Randomized_Cell_Distance_00586780(Cell const &a,Cell const &b);

// Grows a patch of one tile type out from a cell over clear ground (TibSun
// MapGeneratorClass::Place_Tile_Patch): a priority-queue flood fill scored by
// Get_Tile_Patch_Score 0x00586780, claiming at most count cells.
void UnknownMapGenerator::Place_Tile_Patch_00586340(CellClass *cell,int tile,int count,int origin,bool flag)
{
    UnknownVeinNode *nodes=new UnknownVeinNode[10*count];
    UnknownVeinHeap *queue=new UnknownVeinHeap(10*count);
    int i=0;
    queue->Clear();

    int node_count=1;
    Cell position=cell->Fetch_CellID();
    float &first_key=nodes[0].Key;
    nodes[0].Position=position;
    first_key=0;

    MapRegionClass::Get_Cell_Data(cell->Fetch_CellID()).unknown_3c=origin;

    queue->Insert(nodes);

    UnknownVeinNode *node=queue->Remove_Min();
    while(i<count && node!=0) {
        CellClass *cptr=&Map[node->Position];
        cptr->IsoTileIndex=tile;

        int dir=0;
        UnknownVeinNode *newnode=&nodes[node_count];
        for(;dir<8;dir++) {
            Cell newcell=CellClass::Adjacent_Cell(node->Position,dir);
            if(Generation_Cell_In_Bounds_0058da10(newcell)) {
                CellClass *newcellptr=&Map[newcell];
                if(newcellptr->unknown_47b590() || flag && (newcellptr->unknown_47b880() || newcellptr->unknown_47b860())) {
                    if(MapRegionClass::Get_Cell_Data(newcell).unknown_3c!=origin && newcellptr->unknown_11c==0 && newcellptr->OverlayIndex==-1 && newcellptr->OccupierPtr==0) {
                        newnode->Position=newcell;
                        Cell start=cell->Fetch_CellID();
                        float score=Randomized_Cell_Distance_00586780(start,newcell);
                        newnode->Key=score;
                        MapRegionClass::Get_Cell_Data(newcell).unknown_3c=origin;
                        node_count++;
                        queue->Insert(newnode++);
                    }
                }
            }
        }

        i++;
        node=queue->Remove_Min();
    }

    delete[] nodes;
    delete queue;
}
