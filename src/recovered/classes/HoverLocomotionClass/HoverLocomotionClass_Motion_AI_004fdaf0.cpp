// @ref ?Current@FacingClass@@QBE?AUUnknownFacingDir@@XZ=004b8be0
// @ref ?Equal_XY_004bfb60@CoordStruct@@QBEHABU1@@Z=004bfb60
// @ref ?Fast_Atan2@@YAMNN@Z=004ba600
// @ref ?Fast_Sqrt@@YAMN@Z=004ba410
// @ref ?Length@UnknownVector3@@QBEHXZ=0041b780
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?Set_Current@FacingClass@@QAE_NABUUnknownFacingDir@@@Z=004b8b10
// @ref ?Set_Desired@FacingClass@@QAE_NABUUnknownFacingDir@@@Z=004b8a30
// @ref ?While_Moving_004fcbc0@HoverLocomotionClass@@QAEH_N@Z=004fcbc0
// @ref ?Start_Of_Move_004fe0f0@HoverLocomotionClass@@QAEXH@Z=004fe0f0
// @ref ?unknown_coord_a41080@@3UCoordStruct@@A=00a41080
// @ref ?unknown_facing_offsets_851ac0@@3QBUUnknownFacingOffset@@B=00851ac0
// @ref ?unknown_facing_origin_79b630@@3NB=0079b630
// @ref ?unknown_facing_scale_79b628@@3NB=0079b628
// @ref __ftol=0077f110
// @ref __real@8@00000000000000000000=0079b610
// @ref __real@8@3fff8000000000000000=0079a708
// @ref __real@8@4008e100000000000000=0079b608
#include "shared/hover_locomotion.hpp"
#include "shared/rules.hpp"
#include "shared/crt_memory.hpp"
#include "shared/unknown_vector3.hpp"
extern double const unknown_facing_origin_79b630;
extern double const unknown_facing_scale_79b628;
inline int Hover_Destination_Distance_004fdaf0(CoordStruct const &from,CoordStruct const &to)
{
    CoordStruct difference=from-to;
    return (int)Fast_Sqrt((double)difference.X*difference.X+(double)difference.Z*difference.Z+(double)difference.Y*difference.Y);
}

inline UnknownFacingDir Hover_Assign_Direction_004fdaf0(CoordStruct const &from,CoordStruct const &to)
{
    UnknownFacingDir direction;
    if (from.Equal_XY_004bfb60(to)) direction.Raw=0;
    direction=UnknownFacingDir((unsigned short)(int)((Fast_Atan2(double(from.Y)-to.Y,double(to.X)-from.X)-unknown_facing_origin_79b630)*unknown_facing_scale_79b628));
    return direction;
}
inline UnknownFacingDir Hover_Direction_004fdaf0(CoordStruct const &from,CoordStruct const &to)
{
    int from_x=from.X;
    int to_x=to.X;
    return UnknownFacingDir((unsigned short)(int)((Fast_Atan2(double(from.Y)-to.Y,double(to_x)-from_x)-unknown_facing_origin_79b630)*unknown_facing_scale_79b628));
}
inline UnknownVector3 Hover_Vector_Difference_004fdaf0(CoordStruct const &from,CoordStruct const &to)
{
    UnknownVector3 difference;
    difference.X=from.X-to.X;
    difference.Y=from.Y-to.Y;
    difference.Z=from.Z-to.Z;
    return difference;
}
#define Hover_Min_004fdaf0(a,b) ((a)<(b)?(a):(b))
#define Hover_Max_004fdaf0(a,b) ((a)>(b)?(a):(b))
void HoverLocomotionClass::Motion_AI_004fdaf0()
{
    if (Is_Moving() && unknown_24!=unknown_coord_a41080) {
        UnknownFacingDir direction=Hover_Assign_Direction_004fdaf0(LinkedTo->Center_Coord(),unknown_24);
        if (!unknown_70) unknown_30.Set_Desired(direction);
        else unknown_30.Set_Current(direction);
        if ((Is_Powered() && abs(0x2000)>=abs((short)(unknown_30.Current().Raw-direction.Raw))) || unknown_70) {
            if ((unknown_18==unknown_coord_a41080 && Hover_Vector_Difference_004fdaf0(LinkedTo->Center_Coord(),unknown_24).Length()<256) ||
                (unknown_18!=unknown_coord_a41080 && Hover_Destination_Distance_004fdaf0(LinkedTo->Center_Coord(),unknown_18)<256)) {
                unknown_48=0.5;
            } else {
                unknown_48=1.0;
                if (unknown_70) unknown_50=1.0;
            }
        } else unknown_48=0.0;
        if (unknown_48>0.0) {
            unknown_58=1.0;
            if (LinkedTo->Path[0]!=-1 && LinkedTo->Path[0]==LinkedTo->Path[1]) unknown_58=Rules->HoverBoost;
        }
        double acceleration=Hover_Min_004fdaf0(1.0,unknown_58*unknown_48);
        if (acceleration>unknown_50) {
            unknown_50+=1.0/(Rules->HoverAcceleration*900);
            unknown_50=Hover_Min_004fdaf0(unknown_50,acceleration);
        }
        if (acceleration<unknown_50) {
            unknown_50-=1.0/(Rules->HoverBrake*900);
            unknown_50=Hover_Max_004fdaf0(unknown_50,0.0);
        }
        if (unknown_48>0.0 && !unknown_70) {
            CoordStruct coord=unknown_24;
            if (LinkedTo->Path[0]!=-1 && LinkedTo->Path[0]!=8)
                coord=Hover_Adjacent_Coord_004fb9d0(coord,LinkedTo->Path[0]);
            UnknownFacingDir facing=Hover_Direction_004fdaf0(LinkedTo->Center_Coord(),coord);
            LinkedTo->unknown_2e0.Set_Desired(facing);
        }
        return;
    }
    if (Is_Moving() && unknown_24==unknown_coord_a41080) {
        LinkedTo->unknown_slot306(1.0);
        Start_Of_Move_004fe0f0(0);
        While_Moving_004fcbc0(true);
    }
}
#undef Hover_Min_004fdaf0
#undef Hover_Max_004fdaf0
