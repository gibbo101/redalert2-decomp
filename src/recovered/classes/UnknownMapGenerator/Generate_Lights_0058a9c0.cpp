// @ref __real@8@400a8000000000000000=007a6070
// @ref __real@8@3fe1c90fdaa2ea789800=007a5de0
#include "shared/unknown_map_generator.hpp"
#include "shared/facing.hpp"
#include "shared/map_view.hpp"
#include "shared/building_view.hpp"
#include "shared/house.hpp"
#include "shared/house_type.hpp"
#include "shared/building_type_list.hpp"
#include "shared/id_source.hpp"
#include "shared/unknown_globals.hpp"
double __cdecl unknown_sin_4ba480(double);
double __cdecl unknown_cos_4ba4d0(double);
extern char const unknown_light_type_name_7e1b60[];
extern char const unknown_special_name_7cdd70[];
extern int const unknown_light_counts_7a5d7c[4];
extern double const unknown_angle_turn_79c9b8;
extern double const unknown_angle_quarter_79b630;
extern double const unknown_angle_inverse_79b628;
extern double const unknown_facing_radians_79b620;
// @ref ?unknown_light_type_name_7e1b60@@=007e1b60
// @ref ?unknown_special_name_7cdd70@@=007cdd70
// @ref ?unknown_light_counts_7a5d7c@@=007a5d7c
// @ref ?unknown_angle_turn_79c9b8@@=0079c9b8
// @ref ?unknown_angle_quarter_79b630@@=0079b630
// @ref ?unknown_angle_inverse_79b628@@=0079b628
// @ref ?unknown_facing_radians_79b620@@=0079b620
// @ref ?unknown_sin_4ba480@@YANN@Z=004ba480
// @ref ?unknown_cos_4ba4d0@@YANN@Z=004ba4d0
inline void UnknownFacingDir::From_Radian(double angle)
{
    Raw=(unsigned short)(short)((angle-unknown_angle_quarter_79b630)*unknown_angle_inverse_79b628);
}
inline double UnknownFacingDir::As_Radian() const
{
    return ((int)(short)Raw-16383)*unknown_facing_radians_79b620;
}
// Genuine Move_Coord operation; reference inline.h. Actual signed16 direction and original FP observation order.
inline CoordStruct Move_Coord(CoordStruct const &start,UnknownFacingDir const &direction,int distance)
{
    double radians=direction.As_Radian();
    return CoordStruct(start.X+unknown_cos_4ba4d0(radians)*distance,start.Y-unknown_sin_4ba480(radians)*distance,start.Z);
}
#include "shared/map_random.hpp"
// @ref ?unknown_map_random_a705c0@@=00a705c0
// @ref ??RRandom2Class@@QAEHXZ=00638840
// @ref __real@8@3fdf8000000080000000=007a5dd0
// @ref ?Map_Random_Fraction_00579770@@=00579770
double __cdecl Map_Random_Fraction_00579770()
{
    return (unsigned)unknown_map_random_a705c0()*(1.0/4294967295.0);
}
void UnknownMapGenerator::Generate_Lights_0058a9c0()
{
    int lightType=BuildingTypeClass::From_Name(unknown_light_type_name_7e1b60);
    if(lightType!=-1) {
        HouseClass *owner=HouseClass::As_Pointer(HouseTypeClass::Find_Index(unknown_special_name_7cdd70));
        if(owner!=0) {
            bool old=unknown_flag_a40d13;
            unknown_flag_a40d13=true;
            for(int player=0;player<SeedOptions.NumPlayers;++player) {
                Cell waypoint=unknown_id_source_a3d290->Get_Waypoint_Location(player);
                int tries=20;
                int lightCount=unknown_light_counts_7a5d7c[SeedOptions.Time];
                bool clear=false;
                int index;
                while(tries>=0 && !clear) {
                    double angle=Map_Random_Fraction_00579770()*6.283185307179586;
                    clear=true;
                    for(index=0;index<lightCount;++index) {
                        UnknownFacingDir direction;
                        direction.From_Radian(index*unknown_angle_turn_79c9b8/lightCount+angle);
                        CoordStruct position=Move_Coord(Cell_Center(waypoint),direction,8*256);
                        Cell cell(position);
                        if(!BuildingTypes[lightType]->unknown_slot42(cell,owner) || !Map.Unknown_0054AAB0(cell)) { clear=false;break; }
                    }
                    if(clear) {
                        for(index=0;index<lightCount;++index) {
                            UnknownFacingDir direction;
                            direction.From_Radian(index*unknown_angle_turn_79c9b8/lightCount+angle);
                            CoordStruct position=Move_Coord(Cell_Center(waypoint),direction,8*256);
                            Cell cell(position);
                            BuildingClass *light=new BuildingClass(BuildingTypes[lightType],owner);
                            if(!light->unknown_slot53(&CoordStruct(cell.X*256+128,cell.Y*256+128,0),0))delete light;
                        }
                    }
                    --tries;
                }
            }
            unknown_flag_a40d13=old;
        }
    }
}
