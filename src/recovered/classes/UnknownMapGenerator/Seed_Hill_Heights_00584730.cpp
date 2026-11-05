// @ref __real@8@3ff1d1b71758e2196800=007a5fe8
// @ref __real@8@3ff6a3d70a3d70a3d800=007a5fe0
// @ref __real@8@c0008000000000000000=007a5fd8
// @ref _?scale@?1??Seed_Hill_Heights_00584730@UnknownMapGenerator@@QAEXXZ@4NB=007a5d00
// TibSun Seed_Hill_Heights: a random walk of height and volatility over the cell grid, trending with the upper neighbours.
#include "shared/unknown_map_generator.hpp"
#include "shared/map_region.hpp"
#include "shared/map_gaussian.hpp"
#include "shared/cell.hpp"
double __stdcall Map_Clamped_Gaussian_005798f0(double,double,double,double);
inline bool Hill_In_Radar(Cell const &cell)
{
    int x=cell.X;
    int y=cell.Y;
    return y+x>unknown_map_min_a70a1c && x-y<unknown_map_min_a70a1c && y-x<unknown_map_min_a70a1c && y+x<=unknown_map_max_a70a20;
}

void UnknownMapGenerator::Seed_Hill_Heights_00584730()
{
    static double const scale=0.025;

    int i;
    int grid_size=unknown_map_cell_side_84e804*unknown_map_cell_side_84e804;
    double hills=SeedOptions.Ruggedness;
    double height_step=hills*0.0001+0.1;
    double min_volatility=hills*0.0025;
    double max_volatility=hills*0.005;

    if(min_volatility>=scale) {
        for(i=0;i<grid_size;i++) {
            UnknownMapGenerationCell &data=MapRegionClass::Get_Cell_Data(i);
            Cell cell=data.Position;
            if(cell.X!=0||cell.Y!=0) {
                data.unknown_10=0;
                double up_height=0.0;
                double height_trend=0.0;

                if(Hill_In_Radar(cell-Cell(1,1))) {
                    up_height=MapRegionClass::Get_Cell_Data(cell-Cell(1,1)).unknown_08;
                }

                Cell newcell=cell-Cell(1,0);
                if(Hill_In_Radar(newcell)) {
                    UnknownMapGenerationCell &data2=MapRegionClass::Get_Cell_Data(newcell);
                    data.unknown_08+=data2.unknown_08;
                    data.unknown_10=data2.unknown_10;
                    height_trend+=data2.unknown_08-up_height;
                } else {
                    double const &height=data.unknown_08;
                    data.unknown_08=height;
                    data.unknown_10=min_volatility;
                }

                newcell=cell-Cell(0,1);
                if(Hill_In_Radar(newcell)) {
                    UnknownMapGenerationCell &data2=MapRegionClass::Get_Cell_Data(newcell);
                    data.unknown_08=data2.unknown_08+data.unknown_08;
                    data.unknown_10=data2.unknown_10+data.unknown_10;
                    height_trend+=data2.unknown_08-up_height;
                } else {
                    double const &height=data.unknown_08;
                    data.unknown_08=height;
                    data.unknown_10+=min_volatility;
                }

                data.unknown_08*=0.5;
                data.unknown_10*=0.5;
                if(height_trend>0.0) {
                    height_trend=height_step;
                } else if(height_trend<0.0) {
                    height_trend=-height_step;
                }
                if(data.unknown_45[0]) {
                    data.unknown_08=data.unknown_08>0.0?data.unknown_08:0.0;
                    data.unknown_10=0.0025;
                }
                double const mean=0.0;
                data.unknown_10+=Map_Clamped_Gaussian_005798f0(mean,scale,-data.unknown_10,max_volatility-data.unknown_10);

                double min_height=-2.0-data.unknown_08;
                double max_height=2.0-data.unknown_08;
                double trend;
                if(height_trend<min_height) {
                    trend=min_height;
                } else if(height_trend>max_height) {
                    trend=max_height;
                } else {
                    trend=height_trend;
                }
                data.unknown_08+=Map_Clamped_Gaussian_005798f0(trend,data.unknown_10,min_height,max_height);
            }
        }

        for(i=0;i<grid_size;i++) {
            UnknownMapGenerationCell &data=MapRegionClass::Get_Cell_Data(i);
            if(data.unknown_08<0) {
                data.unknown_08=(int)(data.unknown_08-0.5);
            } else if(data.unknown_08>0) {
                data.unknown_08=(int)(data.unknown_08+0.5);
            }
        }
    }
}
