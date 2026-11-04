// BuildingClass::Draw_It 0043A5E0: structure, gate and factory-door shape layers.
// The legacy virtual interface carries Point2D const& and Rect const& as x86 address words (RET8).
#include "shared/building.hpp"
#include "shared/gscreen.hpp"
#include "shared/building_map.hpp"
#include "shared/cell.hpp"
#include "shared/anim.hpp"
#include "shared/tactical.hpp"
#include "shared/rules.hpp"
#define SHAPE_FILE_EMPTY_RECT unknown_static_rect
#include "shared/shape_file.hpp"
// @ref ?Contact2@RadioClass@@=00636e20
// @ref ?Unknown_006A2970@@=006a2970
// @ref ?Coord_To_Pixel_Absolute@Tactical@@QAE?AUPoint2D@@ABU2@@Z=006a2870
// @ref ?unknown_building_depth_shape_85029c@@=0085029c
// @ref ?unknown_496a90@UnknownTimed@@=00496a90
// @ref ?unknown_496ab0@UnknownTimed@@=00496ab0
// @ref ?unknown_496b30@UnknownTimed@@=00496b30
// @ref ?unknown_496b50@UnknownTimed@@=00496b50
// @ref ?Progress_00496C70@UnknownTimed@@=00496c70
void BuildingClass::unknown_slot67(int draw_point_address,int bounds_address)
{
    Cell cell=unknown_slot104();
    ShapeFileStruct const *shape=(ShapeFileStruct const *)unknown_slot26();
    if(shape==0) return;
    if(this!=0 && Kind_Of()==6 && unknown_42c==0 && unknown_slot91()==19) {
        for(int index=0;index<18;index++) {
            if(unknown_454[index]) {
                static_cast<AnimClass *>(unknown_454[index])->unknown_17d=true;
            }
        }
    }
    if(Type->InvisibleInGame) return;
    Point2D depth_point(198,446);
    int z_adjust=Type->NormalZAdjust;
    bool air_product=false;
    if(unknown_slot91()==16) {
        TechnoClass *product=Contact2(0);
        if(product && (product->unknown_slot32()->JumpJet || product->unknown_slot32()->BalloonHover)) {
            air_product=true;
        }
    }
    Point2D const &draw_point=*(Point2D const *)draw_point_address;
    Rect const &bounds=*(Rect const *)bounds_address;
    if(unknown_slot91()==24 && (unknown_2a8.unknown_496a90() || unknown_2a8.unknown_496ab0() || unknown_2a8.unknown_496b30())) {
        int stage=(int)(unknown_2a8.Progress_00496C70()*Type->GateStages);
        if(unknown_2a8.unknown_496ab0()) stage=Type->GateStages-stage;
        if(unknown_2a8.unknown_496b50()) stage=0;
        if(unknown_2a8.unknown_496b30()) stage=Type->GateStages-1;
        if(stage>=Type->GateStages) stage=Type->GateStages-1;
        if(stage<0) stage=0;
        ShapeFileStruct const *gate_shape=(ShapeFileStruct const *)unknown_slot26();
        stage+=(Health_Ratio()<=Rules->unknown_1368 ? Type->GateStages+1 : 0);
        unknown_6d1510(gate_shape,stage,&draw_point,&bounds,0,256,
            z_adjust-Unknown_006A2970(unknown_slot110()),2,1,Map[cell].unknown_10a,0,0,Point2D(0,0),0);
        return;
    }
    if(unknown_slot91()==16) {
        if((air_product && Type->unknown_11b0) || (!air_product && Type->unknown_11a0)) {
            shape=(ShapeFileStruct const *)(air_product ? Type->unknown_11b0 : Type->unknown_11a0);
            z_adjust=-20;
        }
    }
    int mission=unknown_slot91();
    if(mission!=18 && mission!=19) {
        depth_point+=Type->ZShapePointMove;
    }
    Point2D footprint(Type->Width()*256-256,Type->Foundation_Height(false)*256-256);
    depth_point-=unknown_tactical_83996c->Coord_To_Pixel_Absolute(footprint);
    ShapeFileStruct const *depth_shape=unknown_building_depth_shape_85029c;
    if(Type->Width()>=8) depth_shape=0;
    if(bounds.Height>0) {
        int frame=unknown_43be20()<shape->Get_Count()/2 ? unknown_43be20() : shape->Get_Count()/2;
        unknown_6d1510(shape,frame,&draw_point,&bounds,0,256,
            z_adjust-Unknown_006A2970(unknown_slot110()),2,1,Map[cell].unknown_10a+Type->ExtraLight,(int)depth_shape,0,depth_point,0);
    }
    if(Type->unknown_11cc && unknown_42c!=0) {
        unknown_6d1510(Type->unknown_11cc,unknown_43be20(),&draw_point,&bounds,0,256,
            -1-Unknown_006A2970(unknown_slot110()),0,1,Map[cell].unknown_10a+Type->ExtraLight,0,0,Point2D(0,0),0);
    }
    if(unknown_slot91()==16 && ((air_product && Type->unknown_11b8!=0) || (!air_product && Type->unknown_11a8!=0))) {
        if(air_product) {
            unknown_6d1510(Type->unknown_11b8,Health_Ratio()<=Rules->unknown_1368,&draw_point,&bounds,0,256,
                -Unknown_006A2970(unknown_slot110()),0,1,Map[cell].unknown_10a+Type->ExtraLight,0,0,Point2D(0,0),0);
        } else {
            unknown_6d1510(Type->unknown_11a8,Health_Ratio()<=Rules->unknown_1368,&draw_point,&bounds,0,256,
                -Unknown_006A2970(unknown_slot110()),0,1,Map[cell].unknown_10a+Type->ExtraLight,0,0,Point2D(0,0),0);
        }
    }
}
