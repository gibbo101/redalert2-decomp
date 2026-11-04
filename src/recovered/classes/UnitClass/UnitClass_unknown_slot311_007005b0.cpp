// Vehicle shape frames, turret compositing and optional voxel barrels.
#include "shared/unit.hpp"
#include "shared/matrix3d.hpp"
#include "shared/surface.hpp"
#include "shared/weapon_type.hpp"
#include "shared/bullet_type.hpp"
#include "shared/unknown_static_rect.hpp"
#define SHAPE_FILE_EMPTY_RECT unknown_static_rect // Unit.cpp keeps no empty rectangle of its own
#include "shared/palette.hpp"

// Original717F90 copies48 bytes fromAF77A8 to the hidden ECX result and returns it inEAX.
Matrix3D __fastcall Unit_Isometric_View_00717f90();
extern ConvertClass *unknown_drawer_8323c4;
// @ref ?Unit_Isometric_View_00717f90@@=00717f90
// @ref ?unknown_drawer_8323c4@@=008323c4
// @ref ?unknown_6cf670@TechnoClass@@=006cf670
// @ref ?unknown_6cf9d0@TechnoClass@@=006cf9d0
// @ref ?CC_Draw_Shape@@=0049eea0

inline Vector3 Unit_Negated_Vector_007005b0(float const &x,float y,float z)
{
    return Vector3(x,y,z);
}
inline Vector3 operator-(Vector3 const &vector)
{
    return Unit_Negated_Vector_007005b0(-vector.X,-vector.Y,-vector.Z);
}

inline Vector3 Unit_Matrix_Translation_007005b0(Matrix3D const &matrix)
{
    return Vector3(matrix.Row[0][3],matrix.Row[1][3],matrix.Row[2][3]);
}

inline int Unit_Dir_To_4_007005b0(UnknownFacingDir const &direction)
{
    return (((*(unsigned const *)&direction>>13)+1)>>1)%4u;
}

inline double Unit_Direction_Radians32_007005b0(UnknownFacingDir const &direction)
{
    return (Dir_To_32(direction)-8)*-0.19634954084936207;
}

inline bool Unit_Voxel_Loaded_007005b0(UnknownObjectPair const &voxel)
{
    return voxel.unknown_00!=0 && voxel.unknown_04!=0;
}

void UnitClass::unknown_slot311(Point2D point,Rect window,int brightness)
{
    UnknownObjectPair *voxel;
    ShapeFileStruct const *shape=static_cast<ShapeFileStruct const *>(unknown_slot26());
    bool barrel_above=true;
    int frame;
    if (Type->Facings==8 && !unknown_slot48()) frame=(Dir_To_8(unknown_2e0.Current())+1)&7;
    else frame=0;
    if (unknown_5a8>=0) {
        frame=Type->StartFiringFrame+Type->FiringFrames*frame+unknown_5a8/2;
    } else if (!Locomotor.Checked()->Is_Moving() && Type->IdleRate==0) {
        if (unknown_5c0>=0) {
            int death_frame=unknown_5c0/Type->DeathFrameRate;
            int start_death_frame=Type->StartDeathFrame;
            int last_frame=Type->DeathFrames-1;
            if (death_frame>=last_frame) death_frame=last_frame;
            frame=start_death_frame+death_frame;
        } else if (unknown_5a0) {
            if (Type->StandingFrames==0) frame=Type->StartWalkFrame+frame*Type->WalkFrames;
            else frame=Type->StartStandFrame+frame*Type->StandingFrames;
        }
    } else {
        frame=Type->StartWalkFrame+frame*Type->WalkFrames+unknown_430%Type->WalkFrames;
    }
    if (Type->Turret) {
        Point2D shadow_point=point;
        if (unknown_37c) shadow_point.Y-=14;
        CC_Draw_Shape(unknown_surface_83995c,unknown_drawer_8323c4,shape,frame+shape->Get_Count()/2,
                      shadow_point,window,0x2e01,0,unknown_slot176()-2,0,1000,0,0,Point2D(0,0));
        Surface *old_surface=unknown_surface_83995c;
        unknown_surface_83995c=unknown_surface_ad0604;
        Point2D composite_point=Point2D(128,128);
        Matrix3D barrel_matrix;
        Rect composite_window=unknown_surface_83995c->Get_Rect();
        unknown_5bb=true;
        unknown_unit_rect_ad0490=unknown_static_rect;
        voxel=&Type->unknown_c0;
        if (Unit_Voxel_Loaded_007005b0(*voxel)) {
            int key=-1;
            Matrix3D draw_result;
            Matrix3D turret_matrix(*Locomotor.Checked()->Draw_Matrix(&draw_result,&key));
            turret_matrix.Translate_X((float)(Type->TurretOffset/8));
            turret_matrix.Rotate_Z((float)(Unit_Direction_Radians32_007005b0(unknown_2f8.Current())-Unit_Direction_Radians32_007005b0(unknown_2e0.Current())));
            barrel_matrix=turret_matrix;
            Vector3 translation=Unit_Matrix_Translation_007005b0(turret_matrix);
            barrel_matrix.Translate(-translation);
            if (unknown_330.unknown_18) turret_matrix.Translate_X(-unknown_330.unknown_14);
            Vector3 fire_offset=Vector3((float)(unknown_slot231(0)->FLH.X/-8),0.0f,(float)(unknown_slot231(0)->FLH.Z/-8));
            barrel_matrix.Translate(-fire_offset);
            FacingClass pitch=unknown_2c8;
            BulletTypeClass const *projectile=unknown_slot231(0)->WeaponType->Projectile;
            if (projectile->Inviso) {
                int direction=Dir_To_256(pitch.Current());
                if (direction>64 && direction<=128) direction=(direction-64)/3+64;
                else direction=(64-direction)/3+64;
                pitch.Set_Current(UnknownFacingDir((unsigned short)(direction<<8)));
            }
            if (unknown_350.unknown_18) barrel_matrix.Translate_X(-unknown_350.unknown_14);
            barrel_matrix.Rotate_Y((float)-Unit_Direction_Radians32_007005b0(pitch.Current()));
            barrel_matrix.Translate(fire_offset);
            barrel_matrix.Translate(translation);
            barrel_above=Unit_Dir_To_4_007005b0(unknown_2f8.Current())>0 && Unit_Dir_To_4_007005b0(unknown_2f8.Current())<3;
        }
        unknown_slot293(shape,frame,&composite_point,&composite_window,0,256,0,0,0,brightness,0,0,Point2D(0,0),0x2800);
        voxel=&Type->unknown_c0;
        if (Unit_Voxel_Loaded_007005b0(*voxel) && !barrel_above) {
            // Slot246 retains its existing nine-word ABI; the observed references are explicit.
            unknown_slot246(Type->unknown_c0,0,-1,0,composite_window,composite_point,
                            (Unit_Isometric_View_00717f90()*barrel_matrix),brightness,0x2800);
        }
        unsigned turret_frame=((Dir_To_32(unknown_2f8.Current())+4)&31)+8*Type->WalkFrames;
        unknown_slot293(shape,turret_frame,&composite_point,&composite_window,0,256,0,0,0,brightness,0,0,Point2D(0,0),0x2820);
        voxel=&Type->unknown_c0;
        if (Unit_Voxel_Loaded_007005b0(*voxel) && barrel_above) {
            unknown_slot246(Type->unknown_c0,0,-1,0,composite_window,composite_point,
                            (Unit_Isometric_View_00717f90()*barrel_matrix),brightness,0x2820);
        }
        int apparent_brightness=unknown_slot254(brightness);
        unknown_slot312(*old_surface,point,window,apparent_brightness);
        unknown_surface_83995c->Fill_Rect(unknown_unit_rect_ad0490,0);
        unknown_surface_83995c=old_surface;
        unknown_5bb=false;
    } else {
        if (Type->TooBigToFitUnderBridge && unknown_6cf670() && unknown_6cf9d0()==0) {
            unknown_slot293(shape,frame,&point,&window,0,256,-16,0,0,brightness,0,0,Point2D(0,0),0);
            return;
        }
        unknown_slot293(shape,frame,&point,&window,0,256,0,unknown_slot177(),0,brightness,0,0,Point2D(0,0),0);
    }
}
