// @ref ??_GUnknownVeinHeap@@QAEPAXI@Z=0058db20
#include "shared/unknown_map_generator.hpp"
#include "shared/map_region.hpp"
#include "shared/cell.hpp"
#include "shared/map_view.hpp"
#include "shared/id_source.hpp"
#include "shared/fast_math.hpp"
#define RA2_VEIN_HEAP_REMOVE_MIN_IMPLEMENTATION
#include "shared/vein_heap_core.hpp"
void __fastcall Set_Grid_Visit_Byte_0056db10(Cell const &position);
// @ref ?Set_Grid_Visit_Byte_0056db10@@=0056db10
bool __fastcall Generation_Cell_In_Bounds_0058da10(Cell const &position);
// @ref ?Generation_Cell_In_Bounds_0058da10@@=0058da10
// @ref ?Fast_Sqrt@@YAMN@Z=004ba410
namespace seed_0056dba0 {
int __fastcall FUN_0056dba0(short *position)
{
    unsigned index=(unsigned)(int)position[1]*(unsigned)unknown_map_cell_side_84e804+(unsigned)(int)position[0];
    return (int)((unsigned)unknown_map_cells_a70a24+index*sizeof(UnknownMapGenerationCell));
}
}
// @ref ?FUN_0056dba0@=0056dba0
bool UnknownMapGenerator::Init_Start_Points_00583790()
{
    int player=0;
    if(SeedOptions.NumPlayers>0) {
        do {
            Cell seed=unknown_id_source_a3d290->Get_Waypoint_Location(player);
            UnknownVeinNode *nodes=new UnknownVeinNode[800];
            UnknownVeinHeap *heap=new UnknownVeinHeap(800);
            Map.Unknown_0055A550();
            for(CellClass *cell=Map.Unknown_0055A490();cell;cell=Map.Unknown_0055A490()) {
                Cell position=cell->MapCoords;
                reinterpret_cast<UnknownMapGenerationCell *>(seed_0056dba0::FUN_0056dba0((short *)&position))->unknown_3c=0;
            }
            int visited=0;
            int patch=++player;
            heap->Clear();
            int nodeCount=1;
            nodes[0].Position=seed;
            nodes[0].Key=0.0f;
            reinterpret_cast<UnknownMapGenerationCell *>(seed_0056dba0::FUN_0056dba0((short *)&seed))->unknown_3c=patch;
            heap->Insert(&nodes[0]);
            UnknownVeinNode *node=heap->Remove_Min();
            while(node) {
                if(visited>=400)break;
                Set_Grid_Visit_Byte_0056db10(node->Position);
                int facing=0;
                UnknownVeinNode *next=&nodes[nodeCount];
                for(;facing<8;++facing) {
                    Cell adjacent=CellClass::Adjacent_Cell(node->Position,facing);
                    if(Generation_Cell_In_Bounds_0058da10(adjacent) && reinterpret_cast<UnknownMapGenerationCell *>(seed_0056dba0::FUN_0056dba0((short *)&adjacent))->unknown_3c==0) {
                        if(Map[adjacent].unknown_47b590()) {
                            next->Position=adjacent;
                            int dx=(int)adjacent.X-(int)seed.X;
                            int dy=(int)adjacent.Y-(int)seed.Y;
                            int squared=(int)((unsigned)dy*(unsigned)dy+(unsigned)dx*(unsigned)dx);
                            next->Key=Fast_Sqrt((double)squared);
                            reinterpret_cast<UnknownMapGenerationCell *>(seed_0056dba0::FUN_0056dba0((short *)&adjacent))->unknown_3c=patch;
                            ++nodeCount;
                            heap->Insert(next++);
                        }
                    }
                }
                ++visited;
                node=heap->Remove_Min();
            }
            delete[] nodes;
            delete heap;
        } while(player<SeedOptions.NumPlayers);
    }
    return true;
}
