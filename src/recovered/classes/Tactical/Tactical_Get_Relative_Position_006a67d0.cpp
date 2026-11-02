// Point2D Tactical::Unknown_006A67D0() (0x006A67D0): the view position less the
// tactical pixel origin (TibSun Tactical::Get_Relative_Tactical_Position).
#include "shared/tactical.hpp"

Point2D Tactical::Unknown_006A67D0()
{
    Point2D offset(TacPixelX, TacPixelY);
    return unknown_d64 - offset;
}
