#include "shared/map_region.hpp"
#include "shared/map_cell.hpp"
#include "shared/map_view.hpp"
#include "shared/unknown_map_generator.hpp"
double __cdecl Map_Random_Fraction_00579770();
double __stdcall Map_Clamped_Gaussian_005798f0(double,double,double,double);
extern int unknown_tileset_a6e0e8;
// @ref ?unknown_tileset_a6e0e8@@=00a6e0e8
// @ref ?Place_Tile_Patch_00586340@UnknownMapGenerator@@=00586340
// @ref ?Place_Forest_00585dc0@UnknownMapGenerator@@=00585dc0
// @ref ?unknown_471d10@CellClass@@=00471d10
void UnknownMapGenerator::Generate_Vegetation_00585a60()
{
    Map.Unknown_0055A550();
    CellClass *cell=Map.Unknown_0055A490();
    while(cell) {
        Cell position=cell->Fetch_CellID();
        unsigned index=(unsigned)(int)position.Y*(unsigned)unknown_map_cell_side_84e804+(unsigned)(int)position.X;
        unknown_map_cells_a70a24[index].unknown_3c=0;
        cell=Map.Unknown_0055A490();
    }
    Map.Unknown_0055A550();
    cell=Map.Unknown_0055A490();
    while(cell) {
        Cell position=cell->Fetch_CellID();
        unsigned index=(unsigned)(int)position.Y*(unsigned)unknown_map_cell_side_84e804+(unsigned)(int)position.X;
        UnknownMapGenerationCell &data=unknown_map_cells_a70a24[index];
        if(cell->unknown_47b590() && cell->unknown_11c==0 && data.unknown_45[0]==0) {
            Cell origin=cell->Fetch_CellID();
            int originID=(int)((unsigned)(int)origin.Y*512u+(unsigned)(int)origin.X);
            if(Map_Random_Fraction_00579770()<data.unknown_28) {
                Place_Tile_Patch_00586340(cell,unknown_tileset_a6e0e8,(int)Map_Clamped_Gaussian_005798f0(20.0,15.0,4.0,60.0),originID,false);
            }
        }
        cell=Map.Unknown_0055A490();
    }
    Map.Unknown_0055A550();
    cell=Map.Unknown_0055A490();
    while(cell) {
        cell->unknown_471d10();
        cell=Map.Unknown_0055A490();
    }
    int remaining=(int)((SeedOptions.Width*0.1+0.7)*(SeedOptions.Vegetation*0.01)*unknown_2fc);
    for(int attempts=0;remaining>0 && attempts<100;++attempts) {
        Cell position=MapRegionClass::Pick_Random_Clear_Map_Cell_0056d7a0();
        remaining-=Place_Forest_00585dc0(&Map[position],(int)Map_Clamped_Gaussian_005798f0(25.0,10.0,10.0,35.0),Map_Clamped_Gaussian_005798f0(0.2,0.1,0.05,0.4));
    }
}
// @ref __real@8@3ffcccccccccccccd000=0079c260
// @ref __real@8@3ffeb333333333333000=007a6000
// @ref __real@8@4002f000000000000000=007a5398
// @ref __real@8@4003c800000000000000=007a5ff8
// @ref __real@8@40048c00000000000000=007a5f50
// @ref ?Unknown_0055A550@MapClass@@=0055a550
// @ref ?Unknown_0055A490@MapClass@@=0055a490
