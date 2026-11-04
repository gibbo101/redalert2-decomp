// Point2D __fastcall Rectangular_To_Isometric(Point2D point) (0x006A2740): a rectangular point rotated onto
// the isometric axes through 0x006A6800 (TibSun Tactical::Rectangular_To_Isometric). The hidden result comes
// in ecx and the point on the stack, which is why the old TacticalProjection constructor spelling also fit.
#include "shared/tactical.hpp"

Point2D __fastcall Rectangular_To_Isometric(Point2D point)
{
    Point2D iso;
    Unknown_006A6800(point.X, point.Y, &iso.X, &iso.Y);
    return iso;
}
