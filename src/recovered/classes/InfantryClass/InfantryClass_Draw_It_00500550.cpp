// Draw infantry, airborne pod imagery, and the ground shadow.
#include "shared/infantry.hpp"
#include "shared/map_view.hpp"
#include "shared/cell.hpp"
#include "shared/tactical.hpp"
#include "shared/unknown_static_rect.hpp"
// Infantry.cpp already owns the shared empty rectangle initialized by the canonical header-static rows.
// Reuse the shape header's existing fallback-selection API.
#define SHAPE_FILE_EMPTY_RECT unknown_static_rect
#include "shared/palette.hpp"
#include "shared/mix_file_class.hpp"
#include "shared/id_source.hpp"
#include "shared/rules.hpp"
extern "C" GUID const CLSID_BallisticLocomotionClass;
extern "C" ConvertClass *unknown_infantry_drawer_008323c4;
extern "C" ShapeFileStruct const *unknown_infantry_shadow_00a41134;
extern "C" int unknown_infantry_zadjust_007daeb8;
// Existing free declarations from lightning_storm.hpp; no class statics are needed here.
bool Unknown_0051FC50();
bool Unknown_0051FC60();
// @ref _CLSID_BallisticLocomotionClass=007a1fb0
// @ref _unknown_infantry_drawer_008323c4=008323c4
// @ref _unknown_infantry_shadow_00a41134=00a41134
// @ref _unknown_infantry_zadjust_007daeb8=007daeb8
// @ref ?Unknown_0051FC50@@YA_NXZ=0051fc50
// @ref ?Unknown_0051FC60@@YA_NXZ=0051fc60
// @ref ?_com_issue_error@@YGXJ@Z=00795940
// @ref ?Query@?$UnknownComPtr@UIPersist@@$1?unknown_uuid_IPersist_7cf208@@3UGUID@@B@@QAEJABV?$UnknownComPtr@UILocomotion@@$1?unknown_uuid_ILocomotion_7ce600@@3UGUID@@B@@@Z=00454bf0
// @ref ?unknown_slot67@FootClass@@=004c9bc0
// @ref ??_C@_07PGBP@POD?4SHP?$AA@=007daee8
// @ref ??_C@_0M@GHLL@INFSHDW?4SHP?$AA@=007daedc
// @ref ?unknown_level_height_a41130@@3HA=00a41130
// Existing int formals carry Point2D and Rect pointers; their ABI stays unchanged.
void InfantryClass::unknown_slot67(int point_arg,int window_arg)
{
    Point2D const &input=*reinterpret_cast<Point2D const *>(point_arg);
    Rect const &window=*reinterpret_cast<Rect const *>(window_arg);
    Point2D point=input;
    Cell cell=unknown_slot106();
    if (unknown_574==-1) {
        UnknownComPtr<IPersist,&unknown_uuid_IPersist_7cf208> persist(Locomotor);
        GUID class_id;
        persist.Checked()->GetClassID(&class_id);
        if (unknown_slot108()>0 && memcmp(&class_id,&CLSID_BallisticLocomotionClass,sizeof(GUID))==0) {
            ShapeFileStruct const *shape=static_cast<ShapeFileStruct const *>(MixFileClass::Retrieve("POD.SHP"));
            // COM returns a separate two-int point layout. The existing interface
            // spells that result Point2D; this storage view preserves its ABI and
            // applies the evidenced converting constructor without retyping it.
            Point2D shadow=input+Point2D(*reinterpret_cast<RectPoint2D const *>(&Locomotor.Checked()->Shadow_Point()));
            CC_Draw_Shape(unknown_surface_83995c,unknown_infantry_drawer_008323c4,shape,
                Locomotor.Checked()->Drawing_Code(),shadow,window,0x2e01,0,unknown_slot176()-2,0,1000,0,0,Point2D(0,0));
            Map[cell];
            Map[cell];
            unknown_slot293(shape,Locomotor.Checked()->Drawing_Code(),&input,&window,0,256,0,2,0,1000,0,0,Point2D(0,0),0);
        } else {
            ShapeFileStruct const *shape=static_cast<ShapeFileStruct const *>(unknown_slot26());
            if (!shape) return;
            Cell target_cell=unknown_slot106();
            unknown_tactical_83996c->Unknown_006AA510(this,point.X,point.Y);
            int level_light;
            if (Unknown_0051FC50()) level_light=unknown_id_source_a3d290->IonLevel;
            else if (Unknown_0051FC60()) level_light=unknown_id_source_a3d290->unknown_22f4;
            else level_light=unknown_id_source_a3d290->AmbientLevel;
            int brightness;
            if (unknown_79 || ((Map[Position_Coord_004f3f40()].unknown_140&0x10000) &&
                Position_Coord_004f3f40().Z>Map.Unknown_0055A280(Position_Coord_004f3f40())+unknown_bridge_height_a41120/2)) {
                int light=level_light*(unknown_slot108()/(unknown_level_height_a41130*2));
                brightness=Map[target_cell].unknown_10a+light;
            } else {
                brightness=Map[target_cell].unknown_10a+((Map[Position_Coord_004f3f40()].unknown_140&0x10000)?-500:0);
            }
            brightness+=Rules->ExtraInfantryLight;
            int height=unknown_slot108();
            CellClass *current_cell=&Map[Position_Coord_004f3f40()];
            if ((current_cell->unknown_140&0x100) && height>=unknown_bridge_height_a41120) {
                if (((current_cell->unknown_140&0x800) && (current_cell->Adjacent_Cell(0).unknown_140&0x100)) ||
                    (!(current_cell->unknown_140&0x800) && (current_cell->Adjacent_Cell(6).unknown_140&0x100))) height-=unknown_bridge_height_a41120;
            }
            if (height>0 && (unknown_infantry_shadow_00a41134 ||
                (unknown_infantry_shadow_00a41134=static_cast<ShapeFileStruct const *>(MixFileClass::Retrieve("INFSHDW.SHP"))))) {
                CC_Draw_Shape(unknown_surface_83995c,unknown_infantry_drawer_008323c4,unknown_infantry_shadow_00a41134,
                    1,point+Point2D(0,-*reinterpret_cast<signed char const *>(&unknown_59e))+Point2D(0,Unknown_006A2970(height)),window,0x2601,0,-5-Unknown_006A2970(Position_Coord_004f3f40().Z-height),0,1000,0,0,Point2D(0,0));
            }
            // The original reads this storage byte with MOVSX; the current shared bool name remains a hypothesis.
            signed char draw_offset=*reinterpret_cast<signed char const *>(&unknown_59e);
            unknown_slot293(shape,unknown_500350(),&(point+Point2D(0,-draw_offset)),&window,0,256,unknown_infantry_zadjust_007daeb8,2,0,brightness,0,0,Point2D(0,0),0);
        }
    } else unknown_tactical_83996c->Unknown_006AA510(this,point.X,point.Y);
    FootClass::unknown_slot67(reinterpret_cast<int>(&point),window_arg);
}
