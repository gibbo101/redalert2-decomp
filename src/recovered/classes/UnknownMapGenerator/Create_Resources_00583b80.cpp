// @ref __real@8@4002f000000000000000=007a5ce8
// Scatters resource fields over each region's resource cells, then gives every starting position in the
// region a field of its own (TibSun Create_Tiberium; RA2 groups both by map region). The one-line helpers
// add free /Ob2 sites: VectorClass<double>'s constructor stays out of line as in the original.
#include "shared/unknown_map_generator.hpp"
#include "shared/map_region.hpp"
#include "shared/map_gaussian.hpp"
#include "shared/map_random.hpp"
#include "shared/id_source.hpp"
#include "shared/fast_math.hpp"
#include "shared/cell.hpp"
extern DynamicVectorClass<MapRegionClass *> unknown_map_regions_a6fd28;
// @ref ??_7?$DynamicVectorClass@N@@6B@=007a5fac
// @ref ??_7?$VectorClass@N@@6B@=007a5f8c
// @ref ??0?$VectorClass@N@@QAE@IPBN@Z=0058f2d0
// @ref ?Clear@?$VectorClass@N@@UAEXXZ=0058ea60
// @ref ??_G?$VectorClass@N@@UAEPAXI@Z=0058ee30
// @ref ??_G?$DynamicVectorClass@N@@UAEPAXI@Z=0058ee80
// @ref ?Map_Clamped_Gaussian_005798f0@@YGNNNNN@Z=005798f0
inline float Cell_Distance(Cell const &cell,int x,int y)
{
    int dx=cell.X-x;
    int dy=cell.Y-y;
    return Fast_Sqrt((double)(dy*dy+dx*dx));
}

double __stdcall Map_Clamped_Gaussian_005798f0(double mean,double deviation,double minimum,double maximum);
inline int Start_Count(MapRegionClass const *region)
{
    return region->unknown_20;
}

inline bool Rich_Starts(MapSeedClass const &seed)
{
    return seed.Resources==3 && (seed.MapType==1 || seed.MapType==3 || seed.MapType==4);
}

void UnknownMapGenerator::Create_Resources_00583b80()
{
    int waypoint=0;
    bool seek_center;
    int resources=SeedOptions.Resources;
    switch(SeedOptions.MapType) {
        case 0:
            seek_center=resources==3;
            break;
        case 1:
        case 3:
        case 4:
            seek_center=resources!=3;
            break;
        case 2:
            seek_center=true;
            break;
        default:
            seek_center=false;
            break;
    }

    for(int index=0;index<unknown_map_regions_a6fd28.Count();index++) {
        MapRegionClass *region=unknown_map_regions_a6fd28[index];
        DynamicVectorClass<Cell> *&layout=*(DynamicVectorClass<Cell> **)&region->unknown_00;
        if(layout==0) {
            continue;
        }
        int nearest=-1;
        if(seek_center) {
            Cell center(0,0);
            if(region->unknown_20>0) {
                for(int player=0;player<region->unknown_20;player++) {
                    Cell start=unknown_id_source_a3d290->Get_Waypoint_Location(player+waypoint);
                    center.Y+=start.Y;
                    center.X+=start.X;
                }
                center.X/=region->unknown_20;
                center.Y/=region->unknown_20;
            } else {
                center=region->Cells[Map_Random_Range_005797a0(0,region->Cells.Count()-1)];
            }
            int best=500000;
            for(int cell=0;cell<layout->Count();cell++) {
                Cell position=(*layout)[cell];
                float distance=Cell_Distance(position,center.X,center.Y);
                if(distance<(float)best) {
                    best=(int)distance;
                    nearest=cell;
                }
            }
        }
        double percent=SeedOptions.Tiberium*0.01;
        int total=(int)(percent*(unknown_2c0-unknown_2bc)+unknown_2bc);
        double players=region->unknown_20;
        double share=0.5>players?0.5:players;
        int amount=(int)((double)total*share);
        int count=layout->Count();
        if(count==0 || amount==0) {
            continue;
        }
        int per_cell=amount/count;
        for(int field=0;field<layout->Count();field++) {
            int size=(int)((double)per_cell+Map_Clamped_Gaussian_005798f0(0.0,50.0,-100.0,100.0));
            if(size>=0) {
                Create_Resource_Patch_005840a0((*layout)[field],size,field+waypoint+1,field==nearest);
            }
        }

        DynamicVectorClass<double> distances;
        for(int player=0;player<Start_Count(region);player++) {
            double total_distance=0.0;
            Cell start=unknown_id_source_a3d290->Get_Waypoint_Location(player+waypoint);
            for(int cell=0;cell<layout->Count();cell++) {
                Cell position=(*layout)[cell];
                total_distance+=Cell_Distance(position,start.X,start.Y);
            }
            distances.Add(total_distance/(double)layout->Count());
        }

        double closest=9999999.0;
        for(int i=0;i<Start_Count(region);i++) {
            if(distances[i]<closest) {
                closest=distances[i];
            }
        }

        bool rich=Rich_Starts(SeedOptions);
        for(int spot=0;spot<Start_Count(region);spot++) {
            int size=(int)((distances[spot]-closest)*15.0);
            Create_Resource_Patch_005840a0(unknown_id_source_a3d290->Get_Waypoint_Location(spot+waypoint),size+500,spot+waypoint+1,rich);
        }
        waypoint+=Start_Count(region);
    }
}
