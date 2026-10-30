// Existing UnknownVector3 Euclidean length (0041B780), double intermediates then signed FTOL.
#include "shared/unknown_vector3.hpp"
#include "shared/unknown_geometry.hpp"
// Never inlined anywhere in the program (about 200 call sites to 0x0041B630 and 45 to 0x0041B780
// across many units); this unit is the only one that sees the definition, so auto-inlining is off.
#pragma auto_inline(off)
int UnknownVector3::Length() const
{
    double z = Z;
    double y = Y;
    double x = X;
    return (int)unknown_sqrt_4ba410(x * x + y * y + z * z);
}
#pragma auto_inline(on)
