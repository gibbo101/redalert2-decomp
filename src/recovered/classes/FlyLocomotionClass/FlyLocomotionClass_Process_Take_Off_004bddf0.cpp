// @ref ??AMapClass@@QAEAAVCellClass@@ABUCoordStruct@@@Z=00548000
// @ref ?Fast_Atan2@@YAMNN@Z=004ba600
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Release_Held@?$UnknownComPtr@UUnknownFlyInterface@@$1?unknown_uuid_7d80a8@@3UGUID@@B@@QAEXXZ=004bfbc0
// @ref ?Set_Desired@FacingClass@@QAE_NABUUnknownFacingDir@@@Z=004b8a30
// @ref ?_com_issue_error@@YGXJ@Z=00795940
// @ref ?unknown_4b8c80@FacingClass@@QBE?AUUnknownFacingDir@@XZ=004b8c80
// @ref ?unknown_facing_origin_79b630@@3NB=0079b630
// @ref ?unknown_facing_scale_79b628@@3NB=0079b628
// @ref __ftol=0077f110
// @ref _unknown_geometry_j=00865e20
// @ref _unknown_uuid_7d80a8=007d80a8
#include "shared/fly_locomotion.hpp"
#include "shared/fast_math.hpp"
extern double const unknown_facing_scale_79b628;
extern double const unknown_facing_origin_79b630;
inline UnknownFacingDir Fly_Direction_004bddf0(CoordStruct const &from,CoordStruct const &to)
{
    int from_x=from.X;
    int to_x=to.X;
    return UnknownFacingDir((unsigned short)(int)((Fast_Atan2(double(from.Y)-to.Y,double(to_x)-from_x)
        -unknown_facing_origin_79b630)*unknown_facing_scale_79b628));
}
bool FlyLocomotionClass::Process_Take_Off_004bddf0()
{
    int height=LinkedTo->unknown_slot108();
    if (!LinkedTo->unknown_79 && (Loco_Cell(Object_Coord(LinkedTo))->Flags & 0x100) && height>=unknown_geometry_j)
        height-=unknown_geometry_j;
    UnknownFlyPtr flyctrl(LinkedTo);
    int landing_altitude=0;
    if (flyctrl) landing_altitude=flyctrl->unknown_slot3();
    int relative_height=height-landing_altitude;
    int relative_level=unknown_38-landing_altitude;
    unknown_50=false;
    unknown_51=false;
    if (relative_height>relative_level-relative_level/3) {
        LinkedTo->unknown_2f8.Set_Desired(LinkedTo->unknown_2e0.unknown_4b8c80());
    } else if (relative_height>relative_level/2) {
        UnknownFacingDir dir=Fly_Direction_004bddf0(LinkedTo->Center_Coord(),unknown_1c);
        LinkedTo->unknown_2e0.Set_Desired(dir);
        unknown_40=1;
    }
    return true;
}
