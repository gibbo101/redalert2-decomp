// Existing real definitions required by actual Count/index/delete/embedded-destructor operations.
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#define VECTOR_IMPLEMENT_VECTOR_DESTRUCTOR
#define VECTOR_IMPLEMENT_DYNAMIC_DELETE_OBJECT
#define VECTOR_IMPLEMENT_DYNAMIC_DELETE_INDEX
// Actual ECX/RET0 with ignored result; member/name/void source intent remain hypotheses.
#include "shared/unknown_map_generator.hpp"
#include "shared/map_region.hpp"
#include "shared/map_view.hpp"
#include "shared/cell.hpp"
#include "shared/tileset_index.hpp"
extern DynamicVectorClass<MapRegionClass *> unknown_map_regions_a6fd28;
// @ref ?unknown_map_regions_a6fd28@@3V?$DynamicVectorClass@PAVMapRegionClass@@@@A=00a6fd28
// @ref ??1MapRegionClass@@QAE@XZ=0056d970
// @ref ?Initialize_Region_Map_0057bea0@UnknownMapGenerator@@=0057bea0
// @ref ?unknown_0057c4f0@UnknownMapGenerator@@=0057c4f0
// @ref ?unknown_0057c780@UnknownMapGenerator@@=0057c780
// @ref ?unknown_0057c9e0@UnknownMapGenerator@@=0057c9e0
// @ref ?Unknown_0055C2C0@MapClass@@=0055c2c0
// R109 proves this adopted-pointer path; global dynamic identity remains qualified.
MapRegionClass::~MapRegionClass()
{
    if(unknown_00!=0) {
        delete static_cast<DynamicVectorClass<Cell> *>(unknown_00);
        unknown_00=0;
    }
    unknown_map_regions_a6fd28.Delete(this);
    // Cells member destruction is automatic; no outer storage release here.
}
void UnknownMapGenerator::Initialize_Region_Map_0057bea0()
{
    Map.Unknown_0055A550();
    CellClass *cell=Map.Unknown_0055A490();
    while(cell!=0) {
        cell->IsoTileIndex=unknown_tileset_a52580;
        cell=Map.Unknown_0055A490();
    }
    switch(SeedOptions.MapType) {
    case 0: unknown_0057c4f0();break;
    case 1: unknown_0057c780();break;
    case 2: unknown_0057c9e0();break;
    }
    Map.Unknown_0055A550();
    cell=Map.Unknown_0055A490();
    while(cell!=0) {
        if(cell->IsoTileIndex==unknown_tileset_a52580) {
            bool surrounded=true;
            for(int direction=0;direction<8;direction+=2) {
                if(!cell->Adjacent_Cell(direction).unknown_47b590())surrounded=false;
            }
            if(surrounded)cell->IsoTileIndex=0;
        }
        cell=Map.Unknown_0055A490();
    }
    Map.Unknown_0055C2C0(0,0);
    if(unknown_map_cells_a70a24!=0) {
        int remaining=(int)((unsigned int)unknown_map_cell_side_84e804*(unsigned int)unknown_map_cell_side_84e804);
        for(int index=0;remaining>0;--remaining,++index) {
            unknown_map_cells_a70a24[index].RegionIndex=-1;
            unknown_map_cells_a70a24[index].unknown_3c=-1;
        }
    }
    for(int reverse=(int)((unsigned int)unknown_map_regions_a6fd28.Count()-1u);reverse>=0;--reverse) {
        delete unknown_map_regions_a6fd28[reverse];
    }
    unknown_map_region_next_index_a70a28=0;
    Map.Unknown_0055A550();
    cell=Map.Unknown_0055A490();
    while(cell!=0) {
        if(cell->unknown_47b7c0()) {
            for(int direction=0;direction<8;direction+=2) {
                CellClass &neighbor=cell->Adjacent_Cell(direction);
                if(neighbor.unknown_47b590())neighbor.IsoTileIndex=unknown_tileset_a52c60;
            }
        }
        cell=Map.Unknown_0055A490();
    }
}
