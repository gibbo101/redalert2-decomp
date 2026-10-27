// unsigned __fastcall Unknown_00631C40(Point2D const &point) (0x00631C40)
// The hash of a radar point: x + y * 251.
#include "shared/radar.hpp"

unsigned __fastcall Unknown_00631C40(Point2D const &point)
{
    return point.X + point.Y * 251;
}
