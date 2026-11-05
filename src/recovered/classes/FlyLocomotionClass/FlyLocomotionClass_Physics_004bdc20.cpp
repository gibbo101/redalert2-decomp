#include "shared/fly_locomotion.hpp"
#include "shared/fast_math.hpp"
extern double const unknown_move_angle_scale_79b620;
// @ref ?unknown_move_angle_scale_79b620@@3NB=0079b620
int FlyLocomotionClass::Physics_004bdc20(CoordStruct &coord,UnknownFacingDir facing)
{
    int actual=Apparent_Speed();
    if (actual>0) {
        CoordStruct next=Fly_Move_Coord_004bcd50(coord,facing,actual);
        coord=next;
        if (!Map.Unknown_0054AAB0(coord.As_Cell())) return 2;
        return 1;
    }
    return 0;
}
