// int __fastcall Unknown_0060A5C0(Point2D const &point) (0x0060A5C0)
// Half the sum of the absolute coordinates (never called: expanded wherever
// the unit uses it).
#include "shared/particle.hpp"
#include "shared/crt_memory.hpp"

int __fastcall Unknown_0060A5C0(Point2D const &point)
{
    return (abs(point.X) + abs(point.Y)) >> 1;
}
