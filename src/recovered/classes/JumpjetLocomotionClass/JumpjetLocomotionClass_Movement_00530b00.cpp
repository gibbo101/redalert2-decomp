// @ref ??AMapClass@@QAEAAVCellClass@@ABUCoordStruct@@@Z=00548000
// @ref ?Current@FacingClass@@QBE?AUUnknownFacingDir@@XZ=004b8be0
// @ref ?Fast_Cos@@YAMN@Z=004ba4d0
// @ref ?Fast_Sin@@YAMN@Z=004ba480
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Set_Current@FacingClass@@QAE_NABUUnknownFacingDir@@@Z=004b8b10
// @ref ?Unknown_0055A280@MapClass@@QAEHABUCoordStruct@@@Z=0055a280
// @ref ?unknown_450cb0@BuildingClass@@QAE_NPAVObjectClass@@_N@Z=00450cb0
// @ref ?unknown_4717b0@CellClass@@QBEPAVObjectClass@@XZ=004717b0
// @ref ?unknown_531140@JumpjetLocomotionClass@@QAEHXZ=00531140
// @ref ?unknown_func_5d4920@ObjectClass@@QAEXH@Z=005d4920
// @ref ?unknown_jumpjet_cycle_7a5398@@3NB=007a5398
// @ref ?unknown_jumpjet_full_turn_79c9b8@@3NB=0079c9b8
// @ref ?unknown_move_angle_scale_79b620@@3NB=0079b620
// @ref __ftol=0077f110
// @ref __real@8@00000000000000000000=0079b610
// @ref __real@8@3fffc000000000000000=0079d568
#include "shared/jumpjet_locomotion.hpp"
#include "shared/cell.hpp"
#include "shared/building.hpp"
#include "shared/building_type.hpp"
#include "shared/house.hpp"
#include "shared/techno_type.hpp"
#include "shared/unknown_geometry.hpp"
#include "shared/fast_math.hpp"
extern double const unknown_jumpjet_full_turn_79c9b8;
extern double const unknown_jumpjet_cycle_7a5398;
extern double const unknown_move_angle_scale_79b620;
inline CoordStruct Jumpjet_Move_Coord_00530b00(CoordStruct const &start, UnknownFacingDir facing, int distance)
{
    double angle=((short)facing.Raw-0x3fff)*unknown_move_angle_scale_79b620;
    return CoordStruct(
        (int)(double(start.X)+Fast_Cos(angle)*double(distance)),
        (int)(double(start.Y)-Fast_Sin(angle)*double(distance)),start.Z);
}
void JumpjetLocomotionClass::unknown_530b00()
{
    bool need_mark=unknown_4c!=2 && unknown_4c!=3;
    bool was_down=LinkedTo->unknown_74;
    if (need_mark) LinkedTo->unknown_slot71(0);
    else LinkedTo->unknown_74=false;
    if (unknown_70>unknown_68) {
        unknown_68+=Accel;
        unknown_68=unknown_68<Speed?unknown_68:Speed;
    }
    if (unknown_70<unknown_68) {
        unknown_68-=Accel*1.5;
        unknown_68=unknown_68>0?unknown_68:0;
    }
    LinkedTo->unknown_slot306(unknown_68/Speed);
    bool at_destination=LinkedTo->unknown_slot104()==Coord_Cell(unknown_3c);
    if ((unknown_4c==2 || unknown_4c==3) && !NoWobbles)
        unknown_80+=unknown_jumpjet_full_turn_79c9b8/(unknown_jumpjet_cycle_7a5398/Wobbles);
    else unknown_80=0;
    int desired_height=(int)(Fast_Sin(unknown_80)*Deviation+unknown_78);
    int height=LinkedTo->unknown_slot110();
    int ground=Map.Unknown_0055A280(Object_Coord(LinkedTo));
    if ((Map[Object_Coord(LinkedTo)].unknown_140&0x100) && Object_Coord(LinkedTo).Z>=ground+unknown_geometry_g*4)
        ground+=unknown_geometry_j;
    int difference;
    if (unknown_4c!=4 && unknown_4c!=0 && (!at_destination || LinkedTo->unknown_slot32()->BalloonHover))
        difference=height-unknown_531140();
    else difference=height-ground;
    bool moved=false;
    if (difference<desired_height) {
        int height_agl=LinkedTo->unknown_slot108();
        if ((Map[Object_Coord(LinkedTo)].unknown_140&0x100) && !LinkedTo->unknown_79) {
            if (Object_Coord(LinkedTo).Z>=Map.Unknown_0055A280(Object_Coord(LinkedTo))+unknown_geometry_j)
                height_agl-=unknown_geometry_j;
        }
        if (height_agl==0) {
            LinkedTo->unknown_slot59(Object_Coord(LinkedTo));
            LinkedTo->unknown_79=false;
        }
        if (difference+Climb>desired_height) height+=desired_height-difference;
        else height=(int)(height+Climb);
        moved=true;
    } else if (difference>desired_height) {
        if (difference-Climb<desired_height) height+=desired_height-difference;
        else height=(int)(height-Climb);
        if (height<=ground) height=ground;
        difference=difference>0?difference:0;
        moved=true;
    }
    if (LinkedTo->unknown_slot104()!=Coord_Cell(unknown_3c)) {
        if (difference<desired_height/2) unknown_68=0;
        if (difference<desired_height/4) unknown_68=0;
    }
    if (moved) {
        LinkedTo->unknown_func_5d4920(height);
        if (need_mark) LinkedTo->unknown_slot71(0);
    }
    CoordStruct start=Object_Coord(LinkedTo);
    int distance=(int)unknown_68;
    CoordStruct next=Jumpjet_Move_Coord_00530b00(start,unknown_50.Current(),distance);
    LinkedTo->unknown_slot103(next);
    BuildingClass *building=static_cast<BuildingClass *>(Map[next].unknown_4717b0());
    if (building && building->Type->FirestormWall && building->House->unknown_142)
        building->unknown_450cb0(LinkedTo,true);
    LinkedTo->unknown_2e0.Set_Current(unknown_50.Current());
    if (need_mark) LinkedTo->unknown_slot71(1);
    else LinkedTo->unknown_74=was_down;
}
