// TibSun MapGeneratorClass::Seed_Lake (shape reference); the member keeps its unknown_ name until a rename lands.
#include "shared/unknown_map_generator.hpp"
#include "shared/map_region.hpp"
#include "shared/cell.hpp"
#include "shared/map_view.hpp"
#include "shared/tileset_index.hpp"
#define RA2_VEIN_HEAP_REMOVE_MIN_IMPLEMENTATION
#include "shared/vein_heap_core.hpp"
// @ref ?unknown_tileset_a52580@@=00a52580
// @ref ?unknown_tileset_a52c60@@=00a52c60
// @ref ?Grow_Region_00581940@UnknownMapGenerator@@=00581940
// @ref ?Unknown_0055C2C0@MapClass@@=0055c2c0
double __stdcall Weighted_Cell_Distance_0057ec60(Cell const *,Cell const *,int);
// @ref ?Weighted_Cell_Distance_0057ec60@@=0057ec60
bool __fastcall Generation_Cell_In_Bounds_0058da10(Cell const &position);
// @ref ?Generation_Cell_In_Bounds_0058da10@@=0058da10
#include "shared/map_gaussian.hpp"
// @ref ?Next@MapGaussianClass@@QAENXZ=00579830
// @ref ?unknown_map_gaussian_a6fd50@@3VMapGaussianClass@@A=00a6fd50
double __stdcall Map_Clamped_Gaussian_005798f0(double,double,double,double);

// @ref ?Map_Clamped_Gaussian_005798f0@@=005798f0
bool UnknownMapGenerator::unknown_0057e100(Cell const &origin)
{
    unsigned char success=1;
    int spreadLimit=(int)((unsigned)Compute_Water_Cell_Count_0057ec20()-(unsigned)unknown_304);
    if(spreadLimit<=75)return false;
    int capacity=(int)((unsigned)spreadLimit*2u+2u);
    UnknownVeinNode *nodes=new UnknownVeinNode[capacity>100?capacity:100];
    UnknownVeinHeap *heap=new UnknownVeinHeap(capacity>100?capacity:100);
    Map.Unknown_0055A550();
    for(CellClass *cell=Map.Unknown_0055A490();cell;cell=Map.Unknown_0055A490()) {
        Cell position=cell->MapCoords;
        unsigned index=(unsigned)(int)position.Y*(unsigned)unknown_map_cell_side_84e804+(unsigned)(int)position.X;
        unknown_map_cells_a70a24[index].unknown_3c=0;
    }
    int gridSize=(int)((unsigned)unknown_map_cell_side_84e804*(unsigned)unknown_map_cell_side_84e804);
    if(origin==Cell(0,0)) {
        for(int i=0;i<gridSize;++i)MapRegionClass::Get_Cell_Data(i).Marked=0;
        Clear_Region_Border_00581bf0(0,2,-2);
        for(i=0;i<gridSize;++i) {
            int storedRegion=MapRegionClass::Get_Cell_Data(i).RegionIndex;
            if(storedRegion==0 || storedRegion==(int)unknown_308)MapRegionClass::Get_Cell_Data(i).Marked=1;
            else if(storedRegion==-2)MapRegionClass::Get_Cell_Data(i).RegionIndex=0;
        }
    } else {
        for(int i=0;i<gridSize;++i)MapRegionClass::Get_Cell_Data(i).Marked=1;
    }
    int tries=0;
    Cell seed;
    if(origin==Cell(0,0)) {
        for(;;) {
            int x=(int)Map_Random_Range_005797a0(0,Map.MapSize.Width-1);
            int y=(int)Map_Random_Range_005797a0(0,Map.MapSize.Height-1);
            Cell firstOffset=Cell(1,(short)Map.MapSize.Width)+Cell((short)x,(short)(0u-(unsigned)x));
            seed=firstOffset+Cell((short)y,(short)y);
            if(++tries>=200)return false;
            int region=UnknownMapGenerationCell::Get_Region(seed);
            if(region==0 && Map[seed].unknown_47b590() && unknown_map_cells_a70a24[(unsigned)(int)seed.Y*(unsigned)unknown_map_cell_side_84e804+(unsigned)(int)seed.X].Marked) {
                if(tries<200)break;
                return false;
            }
        }
    } else seed=origin;
    int processed=0;
    int maximum=76;
    if(spreadLimit>=76)maximum=spreadLimit;
    double mean=(double)(spreadLimit/3);
    int spreadCount=(int)Map_Clamped_Gaussian_005798f0(mean,(double)(spreadLimit/6),75.0,(double)maximum);
    heap->Clear();
    int used=1;
    nodes[0].Position=seed;
    nodes[0].Key=0.0f;
    unsigned seedIndex=(unsigned)(int)seed.Y*(unsigned)unknown_map_cell_side_84e804+(unsigned)(int)seed.X;
    unknown_map_cells_a70a24[seedIndex].unknown_3c=(int)unknown_308;
    heap->Insert(nodes);
    UnknownVeinNode *node=heap->Remove_Min();
    while(processed<spreadCount) {
        {
            if(node==0 || !success)break;
            Set_Cell_Region_Index_0056e970(node->Position,(int)unknown_308);
            CellClass *current=&Map[node->Position];
            current->IsoTileIndex=unknown_tileset_a52580;
            current->unknown_11a=0;
            int facing=0;
            UnknownVeinNode *next=nodes+used;
            for(;facing<8;facing+=2) {
                Cell adjacent=CellClass::Adjacent_Cell(node->Position,facing);
                if(Generation_Cell_In_Bounds_0058da10(adjacent)) {
                    unsigned index=(unsigned)(int)adjacent.Y*(unsigned)unknown_map_cell_side_84e804+(unsigned)(int)adjacent.X;
                    UnknownMapGenerationCell &data=unknown_map_cells_a70a24[index];
                    if(data.RegionIndex==0 && data.unknown_3c!=(int)unknown_308 && Map[adjacent].unknown_47b590() && data.Marked) {
                        next->Position=adjacent;
                        next->Key=(float)Weighted_Cell_Distance_0057ec60(&seed,&adjacent,processed);
                        data.unknown_3c=(int)unknown_308;
                        ++used;
                        heap->Insert(next++);
                    } else if(data.RegionIndex!=0 && data.RegionIndex!=(int)unknown_308)success=0;
                }
            }
            ++processed;
            node=heap->Remove_Min();
        }
    }
    UnknownVeinNode *remaining=heap->Remove_Min();
    while(remaining) {
        if(!success)break;
        CellClass *current=&Map[remaining->Position];
        unsigned index=(unsigned)(int)remaining->Position.Y*(unsigned)unknown_map_cell_side_84e804+(unsigned)(int)remaining->Position.X;
        UnknownMapGenerationCell &data=unknown_map_cells_a70a24[index];
        if(data.RegionIndex==0 && current->unknown_47b590() && data.Marked) {
            current->IsoTileIndex=unknown_tileset_a52580;
            current->unknown_11a=0;
            data.RegionIndex=(int)unknown_308;
        } else success=0;
        remaining=heap->Remove_Min();
        ++processed;
    }
    if(success) {
        if(processed<=75 || processed<=spreadCount/4)success=0;
        else {
            success=1;
            if(origin==Cell(0,0))success=Map.Unknown_0055C2C0((int)unknown_308,0);
        }
    }
    if(success && origin==Cell(0,0)) {
        success=Grow_Region_00581940((int)unknown_308,1,Rect(0,0,512,512),0,0);
        if(success) {
            int region=(int)unknown_308;
            Map.Unknown_0055A550();
            for(CellClass *cell=Map.Unknown_0055A490();cell;cell=Map.Unknown_0055A490()) {
                int index=UnknownMapGenerationCell::Get_Region(cell->MapCoords);
                if(index==region && (cell->IsoTileIndex==0 || cell->IsoTileIndex==0xffff))cell->IsoTileIndex=unknown_tileset_a52c60;
            }
            success=1;
        }
    }
    delete heap;
    delete[] nodes;
    if(success) {
        unknown_304=(int)((unsigned)unknown_304+(unsigned)processed);
        return true;
    }
    Remap_Region_Tiles_0057e060((int)unknown_308,0,-1,0);
    return false;
}

// @ref __real@8@40059600000000000000=007a5f30
