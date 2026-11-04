// TibSun MapGeneratorClass::Seed_River (shape reference); the member keeps its unknown_ name until a rename lands.
#include "shared/unknown_map_generator.hpp"
#include "shared/map_region.hpp"
#include "shared/cell.hpp"
#include "shared/map_view.hpp"
#include "shared/tileset_index.hpp"
#include "shared/map_random.hpp"
#include "shared/map_gaussian.hpp"
#include "shared/random2.hpp"
#include "shared/crt_memory.hpp"
#include "shared/crt_math.hpp"
#include "shared/fast_math.hpp"
// @ref __real@8@4001afeddf4ddd3ba800=007a5f70
// @ref __real@8@3ffe860a91c16b9b2800=007a5f68
// @ref __real@8@3ffb8f5c28f5c28f6000=007a5f60
// @ref __real@8@3fe5b6000000b6000000=007a5f58
// @ref __real@8@4000a78d3631c681f800=007a5f48
// @ref __real@8@bffda0d97bb4e7870000=007a5f40
// @ref ?Grow_Water_Region_005820b0@UnknownMapGenerator@@=005820b0
// @ref ?Place_Waterfall_0057ff20@UnknownMapGenerator@@=0057ff20
double __stdcall Map_Clamped_Gaussian_005798f0(double,double,double,double);
bool __fastcall Generation_Cell_In_Bounds_0058da10(Cell const &position);
extern double const unknown_random_scale_7a5dd0;
extern double const unknown_lake_chance_7a5cb0;
// @ref ?unknown_lake_chance_7a5cb0@@=007a5cb0
static inline double Random_Fraction()
{
    return (unsigned int)unknown_map_random_a705c0()*unknown_random_scale_7a5dd0;
}
static inline void Clear_River_Region(int region,int const &height_source)
{
    Map.Unknown_0055A550();
    CellClass *cellptr=Map.Unknown_0055A490();
    while(cellptr!=0) {
        Cell position=cellptr->MapCoords;
        UnknownMapGenerationCell &data=MapRegionClass::Get_Cell_Data(position);
        if(data.RegionIndex==region) {
            data.RegionIndex=0;
            data.unknown_4b=0;
            cellptr->IsoTileIndex=0;
            cellptr->unknown_11a=0;
            int height=height_source;
            cellptr->unknown_11b=height;
        }
        cellptr=Map.Unknown_0055A490();
    }
}
bool UnknownMapGenerator::unknown_0057ecf0(Cell const &point,double value,bool flag)
{
    bool orig_subcall=flag;
    unsigned char success=1;
    int waterfall_count=0;
    Cell seed_cell;
    double angle;

    if(point==Cell(0,0)) {
        Cell corner(1,Map.MapSize.Width);
        Cell far_corner=corner+Cell(Map.MapSize.Width,-Map.MapSize.Width)+Cell(Map.MapSize.Height,Map.MapSize.Height)+Cell(-2,0);
        int dir4=Map_Random_Range_005797a0(0,3);
        int x=Map_Random_Range_005797a0(0,Map.MapSize.Width-1);
        int y=Map_Random_Range_005797a0(0,Map.MapSize.Height-1);
        Cell candidates[4];
        candidates[0]=corner+Cell(x,-x);
        candidates[1]=far_corner-Cell(y,y);
        candidates[2]=far_corner-Cell(x,-x);
        candidates[3]=corner+Cell(y,y);
        double base_angle=5.497787143782138-(double)dir4*1.5707963267948966;
        seed_cell=candidates[dir4];
        angle=Map_Clamped_Gaussian_005798f0(base_angle,0.5235987755982988,base_angle-0.7853981633974483,base_angle+0.7853981633974483);
    } else {
        seed_cell=point;
        angle=value;
    }

    if(!Generation_Cell_In_Bounds_0058da10(seed_cell)) {
        return false;
    }

    int seeded_count=0;

    double width_d=(double)SeedOptions.WaterAmount*0.07;
    if(1.0>width_d) {
        width_d=1.0;
    }
    int width_top=(int)width_d;
    double start_width=(double)Map_Random_Range_005797a0(1,width_top);
    double width=start_width;
    int half=(int)start_width/2;
    double width_hi=(double)half+start_width;
    double width_lo=start_width-(double)half;
    int length=Map_Random_Range_005797a0(35,125);
    double cur_x=(double)seed_cell.X+0.5;
    double cur_y=(double)seed_cell.Y+0.5;
    double cur_angle=angle;
    double angle_hi=angle+1.5707963267948966;
    double angle_lo=angle-1.5707963267948966;
    double stop_roll=1.0;

    while(Generation_Cell_In_Bounds_0058da10(Cell((int)cur_x,(int)cur_y)) && success) {
        double step_y=Fast_Cos(cur_angle);
        double step_x=Fast_Sin(cur_angle);
        int span=(int)(width+0.5);
        bool x_run=true;
        bool y_run=true;
        double offset_x=(double)(span-1)*step_x*0.5;
        double px=cur_x-offset_x;
        double offset_y=(double)(span-1)*step_y*0.5;
        double py=cur_y-offset_y;

        if(span>0) {
            int i=span;
            Cell pcell;

            while(true) {
                if(Generation_Cell_In_Bounds_0058da10(Cell((int)px,(int)py))) {
                    pcell=Cell((int)px,(int)py);

                    if(UnknownMapGenerationCell::Get_Region(pcell)==0 && Map[pcell].unknown_47b590() || UnknownMapGenerationCell::Get_Region(pcell)==(int)unknown_308) {
                        if(unknown_map_cells_a70a24) {
                            MapRegionClass::Get_Cell_Data(pcell).RegionIndex=unknown_308;
                        }
                        CellClass *cellptr=&Map[Cell((int)px,(int)py)];
                        cellptr->IsoTileIndex=unknown_tileset_a52580;
                        cellptr->unknown_11a=0;
                    } else {
                        success=false;
                    }
                }

                double next_x=px+step_x;
                if((int)px!=(int)next_x) {
                    x_run=false;
                }

                double next_y=py+step_y;
                if((int)py!=(int)next_y) {
                    y_run=false;
                }

                px=next_x;
                py=next_y;
                i--;

                if(i==0) {
                    break;
                }
            }
        }

        if(fabs(step_y)>fabs(step_x)) {
            y_run=false;
        } else {
            x_run=false;
        }

        if(!flag && (x_run || y_run) && waterfall_count<1 && (double)abs((int)(cur_angle-angle))<0.7853981633974483) {
            if(unknown_310) {
                if(seeded_count>length) {
                    int type;

                    if(x_run) {
                        type=(step_y>0.0)?2:6;
                    } else {
                        type=(step_x>0.0)?0:4;
                    }

                    bool placed=false;
                    Cell from((int)(px-step_x),(int)(py-step_y));
                    Cell to((int)(cur_x-offset_x),(int)(cur_y-offset_y));
                    Place_Waterfall_0057ff20(unknown_308,to,from,type,placed,cur_x,cur_y);

                    if(placed) {
                        unknown_308++;
                        waterfall_count++;
                    }
                }
            }
        }

        cur_x+=step_y;
        cur_y-=step_x;

        if(Random_Fraction()<0.01) {
            if(success) {
                if(!flag && waterfall_count==0) {
                    flag=true;
                    double branch_mean=cur_angle+1.5707963267948966;
                    double branch_lo=cur_angle+0.5235987755982988;
                    double branch_hi=cur_angle+2.6179938779914944;
                    double branch_deviation=0.5235987755982988;
                    if(branch_mean-branch_deviation>branch_hi || branch_mean+branch_deviation<branch_lo) {
                        branch_deviation=(branch_hi-branch_lo)*0.5;
                        branch_mean=branch_deviation+branch_lo;
                    }
                    double branch_angle;
                    do {
                        branch_angle=unknown_map_gaussian_a6fd50.Next()*branch_deviation+branch_mean;
                    } while(branch_angle<branch_lo || branch_angle>branch_hi);
                    success=unknown_0057ecf0(Cell((int)px,(int)py),branch_angle,true);
                }
            }
        }

        if(seeded_count>5) {
            double delta_angle=Map_Clamped_Gaussian_005798f0(0.0,0.3141592653589793,angle_lo-cur_angle,angle_hi-cur_angle);
            cur_angle+=delta_angle;
        }

        if(half>0) {
            double step_hi=width_hi-width;
            double step_lo=width_lo-width;
            double step_dev=0.5;
            double step_mean=0.0;
            if(step_mean-step_dev>step_hi || step_mean+step_dev<step_lo) {
                step_dev=(step_hi-step_lo)*0.5;
                step_mean=step_dev+step_lo;
            }
            double delta_width;
            do {
                delta_width=unknown_map_gaussian_a6fd50.Next()*step_dev+step_mean;
            } while(delta_width<step_lo || delta_width>step_hi);
            width+=delta_width;
        }

        stop_roll=Random_Fraction();
        seeded_count++;

        if(stop_roll<0.005) {
            break;
        }
    }

    if(seeded_count<40) {
        success=false;
    }

    if(stop_roll<0.005) {
        if(Generation_Cell_In_Bounds_0058da10(Cell((int)cur_x,(int)cur_y)) && success) {
            if(!unknown_0057e100(Cell((int)cur_x,(int)cur_y))) {
                success=false;
            }
        }
    }

    if(!orig_subcall && success) {
        success=Map.Unknown_0055C2C0(unknown_308,0);

        if(success) {
            success=Grow_Region_00581940(unknown_308,1,Rect(0,0,0x200,0x200),0,0);
            int region_id=unknown_308;
            Map.Unknown_0055A550();
            CellClass *cptr=Map.Unknown_0055A490();

            while(cptr!=0) {
                if(UnknownMapGenerationCell::Get_Region(cptr->MapCoords)==region_id && (cptr->IsoTileIndex==0 || cptr->IsoTileIndex==0xffff)) {
                    cptr->IsoTileIndex=unknown_tileset_a52c60;
                }
                cptr=Map.Unknown_0055A490();
            }
        }
    }

    bool raised=false;

    if(waterfall_count==0 && success && unknown_30c==4 && !orig_subcall) {
        if(Random_Fraction()<unknown_lake_chance_7a5cb0) {
            Rect bounds(0,0,0x200,0x200);

            if(Grow_Water_Region_005820b0(unknown_308,0.01f,bounds,seed_cell,true)) {
                success=Grow_Region_00581940(unknown_308,6,Rect(0,0,0x200,0x200),0,0);

                if(success) {
                    int region_id=unknown_308;
                    Map.Unknown_0055A550();
                    CellClass *cptr=Map.Unknown_0055A490();

                    while(cptr!=0) {
                        Cell c=cptr->MapCoords;
                        int rid=UnknownMapGenerationCell::Get_Region(c);

                        if(rid!=region_id) {
                            cptr->unknown_11b+=4;
                        }

                        cptr=Map.Unknown_0055A490();
                    }

                    raised=true;
                }
            } else {
                success=false;
            }
        }
    }

    if(!orig_subcall && success && waterfall_count==0) {
        if(!raised) {
            success=Grow_Region_00581940(unknown_308,2,Rect(0,0,0x200,0x200),0,0);
        }
    } else if(waterfall_count>0) {
        if(success) {
            success=Grow_Region_00581940(unknown_308,2,Rect(0,0,0x200,0x200),1,unknown_30c);
        }
    }

    if(success) {
        if(raised) {
            unknown_30c+=4;
        }

        unknown_304+=seeded_count;
        return true;
    }

    Clear_River_Region(unknown_308,unknown_30c);

    if(waterfall_count>0) {
        Clear_River_Region(unknown_308-1,unknown_30c);
    }

    return false;
}
