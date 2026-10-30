// Existing UnknownVector3 coordinate-difference constructor (0041B630).
#include "shared/unknown_vector3.hpp"
// Never inlined anywhere in the program (about 200 call sites to 0x0041B630 and 45 to 0x0041B780
// across many units); this unit is the only one that sees the definition, so auto-inlining is off.
#pragma auto_inline(off)
UnknownVector3::UnknownVector3(int x, int y, int z) : X(x), Y(y), Z(z) {}
#pragma auto_inline(on)
