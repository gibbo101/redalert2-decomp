#include "shared/fly_locomotion.hpp"
#include "shared/fast_math.hpp"
extern double const unknown_move_angle_scale_79b620;
// @ref ?unknown_move_angle_scale_79b620@@3NB=0079b620
inline CoordStruct Fly_Move_Coord_004bdc20(CoordStruct const &start,UnknownFacingDir facing,int distance)
{
    double angle=((short)facing.Raw-0x3fff)*unknown_move_angle_scale_79b620;
    return CoordStruct((int)(double(start.X)+Fast_Cos(angle)*double(distance)),
        (int)(double(start.Y)-Fast_Sin(angle)*double(distance)),start.Z);
}
int FlyLocomotionClass::Physics_004bdc20(CoordStruct &coord,UnknownFacingDir facing)
{
    int actual=Apparent_Speed();
    if (actual>0) {
        CoordStruct next=Fly_Move_Coord_004bdc20(coord,facing,actual);
        coord=next;
        if (!Map.Unknown_0054AAB0(Cell(coord))) return 2;
        return 1;
    }
    return 0;
}
