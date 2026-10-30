#include "shared/map_region.hpp"
#include "shared/unknown_map_generator.hpp"
#include "shared/map_cell.hpp"
#include "shared/map_view.hpp"
void Set_Generation_Path_Tile_Indices_0058d9d0();
// @ref ?Set_Generation_Path_Tile_Indices_0058d9d0@@=0058d9d0
#include "shared/map_gaussian.hpp"
// @ref ?Next@MapGaussianClass@@QAENXZ=00579830
// @ref ?unknown_map_gaussian_a6fd50@@3VMapGaussianClass@@A=00a6fd50
double __stdcall Map_Clamped_Gaussian_005798f0(double mean,double deviation,double minimum,double maximum)
{
    if(maximum<mean-deviation || mean+deviation<minimum) {
        deviation=(maximum-minimum)*0.5;
        mean=deviation+minimum;
    }
    double value;
    do {
        value=unknown_map_gaussian_a6fd50.Next()*deviation+mean;
    } while(value<minimum || value>maximum);
    return value;
}

// @ref ?Is_Cliff_0047b5e0@CellClass@@=0047b5e0
// @ref ?Create_Urban_Area_00586b40@UnknownMapGenerator@@=00586b40
// @ref ?Generate_Urban_Roads_00587330@UnknownMapGenerator@@=00587330
// @ref ?Generate_Urban_Buildings_00587cf0@UnknownMapGenerator@@=00587cf0
// @ref ?Generate_Urban_Units_00588100@UnknownMapGenerator@@=00588100
bool __fastcall Neighborhood_Is_Clear_00588380(Cell const &center);
namespace seed_0056dac0 { bool __fastcall FUN_0056dac0(short *position); }
void UnknownMapGenerator::Generate_Urban_Areas_00586800()
{
    int count=(int)((SeedOptions.UrbanPresence+0.32)*3);
    int tries=0,placed=0;
    Set_Generation_Path_Tile_Indices_0058d9d0();
    while(tries<10) {
        if(placed>=count)break;
        Cell position;
        position.X=0;position.Y=0;
        int localTries=0;
        for(;;) {
            position=MapRegionClass::Pick_Random_Clear_Map_Cell_0056d7a0();
            if(++localTries>=20)break;
            if(seed_0056dac0::FUN_0056dac0((short *)&position) || Neighborhood_Is_Clear_00588380(position))break;
        }
        if(Map_Random_Fraction_00579770()<1.0-SeedOptions.UrbanPresence) {
            if(Generate_Rural_Roads_0058a1b0(position)) {
                Generate_Rural_Buildings_00589ac0(position);
                Generate_Rural_Units_00589f00(position);
                ++placed;
            }
        } else {
            if(localTries!=20) {
                int mean=(int)((unsigned)Map.MapSize.Width*(unsigned)Map.MapSize.Height*2u)/30;
                int size=(int)Map_Clamped_Gaussian_005798f0((double)mean,300.0,100.0,2000.0);
                DynamicVectorClass<Cell> *cells=Create_Urban_Area_00586b40(position,size);
                if(cells) {
                    Generate_Urban_Roads_00587330(*cells);
                    Generate_Urban_Buildings_00587cf0(*cells);
                    Generate_Urban_Units_00588100(*cells);
                    Generate_Urban_Pavement_005890b0(*cells);
                    ++placed;
                    delete cells;
                }
            }
            ++tries;
        }

    }
}
// @ref __real@8@3ffda3d70a3d70a3d800=007a6030
// @ref __real@8@40079600000000000000=007a6028
// @ref __real@8@4009fa00000000000000=007a6020

// Packed coordinate ECX and AL-only result; freefastcall/constreference/bool/name are source hypotheses.
#include "shared/coord.hpp"
#include "shared/map_cell.hpp"
#include "shared/map_view.hpp"
bool __fastcall Unknown_Cell_Predicate_0047b5e0(CellClass *cell);
// @ref ?Unknown_Cell_Predicate_0047b5e0@@=0047b5e0
bool __fastcall Neighborhood_Is_Clear_00588380(Cell const &center)
{
    int centerY=center.Y;
    int top=centerY-7;
    int centerX=center.X;
    int right=centerX+7;
    int bottom=centerY+7;
    for(int x=centerX-7;x<right;++x) {
        for(int y=top;y<bottom;++y) {
            Cell position((short)x,(short)y);
            if(Unknown_Cell_Predicate_0047b5e0(&Map[position]))return false;
        }
    }
    return true;
}
