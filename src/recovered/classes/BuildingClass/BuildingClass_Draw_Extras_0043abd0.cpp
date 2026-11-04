// BuildingClass::Draw_Extras 0043ABD0: departing products, door shapes, turret and barrel voxels.
#include "shared/building.hpp"
#include "shared/gscreen.hpp"
#include "shared/building_map.hpp"
#include "shared/cell.hpp"
#include "shared/tactical.hpp"
#include "shared/rules.hpp"
#include "shared/id_source.hpp"
#include "shared/anim.hpp"
#include "shared/matrix3d.hpp"
extern bool unknown_voxel_cache_839a58;
extern int unknown_barrel_dir_adjust_7cf658;
extern bool unknown_barrel_make_visible_7cf65c;
extern Rect unknown_rect_839630;
Matrix3D __fastcall Aircraft_Isometric_View_Matrix_00717f90();
inline double Barrel_Direction_Angle_00453900(UnknownFacingDir const &direction);
// @ref ?unknown_voxel_cache_839a58@@=00839a58
// @ref ?unknown_barrel_dir_adjust_7cf658@@=007cf658
// @ref ?unknown_barrel_make_visible_7cf65c@@=007cf65c
// @ref ?unknown_rect_839630@@=00839630
// @ref ?Aircraft_Isometric_View_Matrix_00717f90@@YI?AVMatrix3D@@XZ=00717f90
// @ref ?Coord_To_Pixel@Tactical@@=006a29d0
// @ref ?Unknown_005683C0@MapClass@@=005683c0
// @ref ?unknown_453900@BuildingClass@@=00453900
// @ref ?Translate@Matrix3D@@QAEXABUVector3@@@Z=005900f0
// @ref ??D@YI?AVMatrix3D@@ABV0@0@Z=00591180
inline int Draw_Dir4_0043abd0(UnknownFacingDir const &direction)
{
    return (((*(unsigned const *)&direction >> 13)+1)>>1)&3;
}
inline bool Barrel_Side_0043abd0(FacingClass &facing)
{
    return Draw_Dir4_0043abd0(facing.Current())>0 && Draw_Dir4_0043abd0(facing.Current())<3;
}
void BuildingClass::unknown_slot284(Point2D const &xy,Rect const &bounds)
{
    Cell cell=unknown_slot104();
    if(unknown_slot91()==16 && (unknown_2a8.unknown_496a90() || unknown_2a8.unknown_496b30() || unknown_2a8.unknown_496b50() || unknown_2a8.unknown_496ab0()) && unknown_370) {
        for(int index=0;index<RadioLinks.Length();index++) {
            TechnoClass *product=Contact2(index);
            if(product && !product->unknown_76 && product->Kind_Of()!=6) {
                CoordStruct destination=product->unknown_slot19(0);
                destination.Z=product->Position_Coord_004f3f40().Z;
                if(!unknown_b263d8 || unknown_flag_a40d13 || !(unknown_id_source_a3d290->unknown_000&0x1000) ||
                   (!Map.Unknown_005683C0(product->Position_Coord_004f3f40()) && !Map.Unknown_005683C0(destination))) {
                    Point2D point;
                    unknown_tactical_83996c->Coord_To_Pixel(product->unknown_slot42(),point);
                    product->unknown_slot67((int)&point,(int)&bounds);
                }
            }
        }
    }
    if(unknown_slot91()==16 && Type->DoorAnimData_11c0) {
        if(unknown_2a8.unknown_496b50() || unknown_2a8.unknown_496a90() || unknown_2a8.unknown_496ab0() || unknown_2a8.unknown_496b30()) {
            int stage=(int)(unknown_2a8.Progress_00496C70()*Type->DoorStages);
            if(unknown_2a8.unknown_496ab0()) stage=Type->DoorStages-stage;
            if(unknown_2a8.unknown_496b50()) stage=0;
            if(stage>=Type->DoorStages) stage=Type->DoorStages-1;
            if(stage<0) stage=0;
            if(Health_Ratio()<=Rules->unknown_1368 && Type->DamagedDoor) stage+=Type->DoorStages;
            int z_adjust=-5-Unknown_006A2970(unknown_slot110());
            unknown_6d1510(Type->DoorAnimData_11c0,stage,&xy,&bounds,0,256,z_adjust,0,0,Map[cell].unknown_10a,0,0,Point2D(0,0),0);
            if(unknown_2a8.unknown_496ab0() && stage==0) unknown_75=true;
        }
    }
    if(Type->TurretAnimIsVoxel) {
        bool construction=false;
        if((Mission==18 || MissionQueue==18) && Stage<Type->AnimFrames[0].unknown_04+Type->AnimFrames[0].unknown_00-1) construction=true;
        if(((Mission!=19 || Stage<=0) && !construction) || Type->Artillary) {
            int key;
            if(unknown_voxel_cache_839a58) key=Dir_To_32(unknown_2e0.Current());
            else key=-1;
            Matrix3D matrix;
            matrix.Make_Identity();
            if(Type->unknown_b8.unknown_00) {
                matrix.Rotate_Z((float)Barrel_Direction_Angle_00453900(unknown_2e0.Current()));
                matrix.Translate_X((float)(Type->TurretOffset/8));
                Matrix3D barrel_matrix;
                barrel_matrix=matrix;
                Vector3 origin=matrix.Get_Translation();
                barrel_matrix.Translate(-origin);
                if(unknown_330.unknown_18!=0) {
                    matrix.Translate_X(-unknown_330.unknown_14);
                    key=-1;
                }
                if(unknown_350.unknown_18!=0) {
                    barrel_matrix.Translate_X(-unknown_350.unknown_14);
                    key=-1;
                }
                barrel_matrix.Rotate_Y((float)-Barrel_Direction_Angle_00453900(unknown_2c8.Current()));
                barrel_matrix.Translate(origin);
                Point2D draw_point=xy+Point2D(Type->Anims[9].Offset.X,Type->Anims[9].Offset.Y);
                bool draw_barrel=Barrel_Side_0043abd0(unknown_2e0);
                if(!draw_barrel) {
                    UnknownObjectPair *voxel=&Type->unknown_c0;
                    if(voxel->unknown_00 && voxel->unknown_04) {
                        unknown_slot246(Type->unknown_c0,0,key,&Type->unknown_250,bounds,draw_point,
                            Aircraft_Isometric_View_Matrix_00717f90()*barrel_matrix,Map[cell].unknown_10a,0);
                    }
                }
                unknown_slot246(Type->unknown_b8,0,key,&Type->unknown_228,bounds,draw_point,
                    Aircraft_Isometric_View_Matrix_00717f90()*matrix,Map[cell].unknown_10a,0);
                if(draw_barrel) {
                  UnknownObjectPair *voxel=&Type->unknown_c0;
                  if(voxel->unknown_00 && voxel->unknown_04) {
                    unknown_slot246(Type->unknown_c0,0,key,&Type->unknown_250,bounds,draw_point,
                        Aircraft_Isometric_View_Matrix_00717f90()*barrel_matrix,Map[cell].unknown_10a,0);
                  }
                }
            } else if(Type->unknown_c0.unknown_00 && Type->unknown_c0.unknown_04) {
                Vector3 origin=matrix.Get_Translation();
                matrix.Translate(-origin);
                matrix.Rotate_Z((float)Barrel_Direction_Angle_00453900(unknown_2e0.Current()));
                matrix.Rotate_Y((float)-Barrel_Direction_Angle_00453900(unknown_2c8.Current()));
                matrix.Translate(origin);
                unknown_slot246(Type->unknown_c0,0,key,&Type->unknown_250,bounds,xy+Point2D(Type->Anims[9].Offset.X,Type->Anims[9].Offset.Y),
                    Aircraft_Isometric_View_Matrix_00717f90()*matrix,Map[cell].unknown_10a,0);
            }
        }
    } else if(Type->BarrelAnimIsVoxel) {
        bool construction=false;
        if((Mission==18 || MissionQueue==18) && Stage<Type->AnimFrames[0].unknown_04+Type->AnimFrames[0].unknown_00-1) construction=true;
        if((Mission!=19 || Stage<=0) && !construction) {
            Matrix3D matrix=unknown_453900();
            int direction=(unknown_barrel_dir_adjust_7cf658+Dir_To_32(unknown_2e0.Current()))%32;
            bool in_front=direction<=16;
            AnimClass *animation=static_cast<AnimClass *>(unknown_454[9]);
            if(in_front && animation) {
                if(unknown_barrel_make_visible_7cf65c) animation->unknown_17d=false;
                animation->unknown_slot63(&unknown_rect_839630,true,false);
                animation->unknown_17d=true;
            }
            unknown_slot246(Type->unknown_c0,0,-1,&Type->unknown_214,bounds,xy+Point2D(Type->Anims[9].Offset.X,Type->Anims[9].Offset.Y),
                Aircraft_Isometric_View_Matrix_00717f90()*matrix,Map[cell].unknown_10a,0);
            if(!in_front && animation) {
                if(unknown_barrel_make_visible_7cf65c) animation->unknown_17d=false;
                animation->unknown_slot63(&unknown_rect_839630,true,false);
                animation->unknown_17d=true;
            }
        }
    }
}
