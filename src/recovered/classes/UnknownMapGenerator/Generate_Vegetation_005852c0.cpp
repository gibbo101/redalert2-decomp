// TibSun Generate_Vegetation: per-map random patch means, ground cover by each cell's chances, forests, then rocks.
// Overlay_Is_Clear and Set_Overlay are one-line accessors: free /Ob2 sites that keep the Cell ctor out of line at the rock pick, as in the original.
#include "shared/map_region.hpp"
#include "shared/cell.hpp"
#include "shared/map_view.hpp"
#include "shared/unknown_map_generator.hpp"
#include "shared/tileset_index.hpp"
double __cdecl Map_Random_Fraction_00579770();
double __stdcall Map_Clamped_Gaussian_005798f0(double,double,double,double);
unsigned __fastcall Map_Random_Range_005797a0(unsigned,unsigned);
int __fastcall unknown_cells_428ac0();
extern int unknown_tileset_a6e0e8;
extern int unknown_tileset_a6cf4c;
// @ref __real@8@4005a000000000000000=007a6008
// @ref __real@8@3fe3a8000000a8000000=007a6010
// @ref ?unknown_cells_428ac0@@YIHXZ=00428ac0
// @ref ?unknown_tileset_a6cf4c@@3HA=00a6cf4c
// @ref ?Unknown_00472540@CellClass@@QAEXH@Z=00472540
// Same-file bodies of MapRegionClass::Pick_Random_Map_Cell 0x56D720 and Pick_Random_Clear_Map_Cell 0x56D7A0,
// accepted in their own population; this unit expands them.
inline bool Overlay_Is_Clear(CellClass const *cell)
{
    return cell->OverlayIndex==-1;
}

inline void Set_Overlay(CellClass *cell,int overlay)
{
    cell->OverlayIndex=overlay;
}

inline Cell Pick_Random_Map_Cell()
{
    int gridSize=unknown_map_cell_side_84e804*unknown_map_cell_side_84e804;
    unsigned index;
    do { index=Map_Random_Range_005797a0(0,gridSize-1); }
    while((unsigned char)unknown_map_cells_a70a24[index].Position.Equal_004fef20(Cell(0,0)));
    return unknown_map_cells_a70a24[index].Position;
}

inline Cell Pick_Random_Clear_Map_Cell()
{
    int tries=0;
    for(;;) {
        Cell position=Pick_Random_Map_Cell();
        if(++tries>200)return Cell(0,0);
        if(Map[position].unknown_47b590())return position;
    }
}

void UnknownMapGenerator::Generate_Vegetation_005852c0()
{
    Map.Unknown_0055A550();
    CellClass *cell=Map.Unknown_0055A490();
    while(cell) {
        MapRegionClass::Get_Cell_Data(cell->Fetch_CellID()).unknown_3c=0;
        cell=Map.Unknown_0055A490();
    }

    Map.Unknown_0055A550();
    cell=Map.Unknown_0055A490();

    int green_mean=Map_Random_Range_005797a0(20,40);
    int sand_mean=Map_Random_Range_005797a0(20,40);
    int rough_mean=Map_Random_Range_005797a0(20,40);

    while(cell) {
        UnknownMapGenerationCell &data=MapRegionClass::Get_Cell_Data(cell->Fetch_CellID());
        if(cell->unknown_47b590() && cell->unknown_11c==0 && cell->OverlayIndex==-1 && cell->OccupierPtr==0 && data.unknown_45[0]==0) {
            Cell origin=cell->Fetch_CellID();
            int originID=(int)((unsigned)(int)origin.Y*512u+(unsigned)(int)origin.X);
            if(Map_Random_Fraction_00579770()<data.unknown_18) {
                Place_Tile_Patch_00586340(cell,unknown_tileset_a6e0e8,(int)Map_Clamped_Gaussian_005798f0(green_mean,20.0,4.0,80.0),originID,false);
            } else if(Map_Random_Fraction_00579770()<data.unknown_28) {
                Place_Tile_Patch_00586340(cell,unknown_tileset_a6cf4c,(int)Map_Clamped_Gaussian_005798f0(sand_mean,20.0,4.0,80.0),originID,false);
            } else if(Map_Random_Fraction_00579770()<data.unknown_20) {
                Place_Tile_Patch_00586340(cell,unknown_tileset_a52c60,(int)Map_Clamped_Gaussian_005798f0(rough_mean,20.0,4.0,80.0),originID,false);
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
    int tries;
    for(tries=0;remaining>0 && tries<100;++tries) {
        Cell position=Pick_Random_Clear_Map_Cell();
        remaining-=Place_Forest_00585dc0(&Map[position],(int)Map_Clamped_Gaussian_005798f0(25.0,10.0,10.0,35.0),Map_Clamped_Gaussian_005798f0(0.2,0.1,0.05,0.4));
    }

    int rock_count=Map_Random_Range_005797a0(0,unknown_cells_428ac0()/200);
    int placed=0;
    for(tries=0;tries<rock_count*5 && placed<rock_count;tries++) {
        Cell position=Pick_Random_Map_Cell();
        CellClass *target=&Map[position];
        if(Overlay_Is_Clear(target)) {
            if(target->unknown_47b9a0()) {
                Set_Overlay(target,Map_Random_Range_005797a0(0,4)+0xa8);
            } else if(target->unknown_47b590() || target->unknown_47b9c0()) {
                Set_Overlay(target,Map_Random_Range_005797a0(0,4)+0xad);
            }
            target->OverlayData=0;
            target->Unknown_00472540(-1);
            placed++;
        }
    }
}
