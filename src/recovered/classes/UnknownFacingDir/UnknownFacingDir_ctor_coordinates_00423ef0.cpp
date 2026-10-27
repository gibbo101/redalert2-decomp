// UnknownFacingDir coordinate constructor00423EF0: independent99code+13padding.
// Equal XY first writes Raw0 but still computes the direction afterward.
// Preserve the original four-byte value copy; the second word is not initialized.
#include "shared/facing.hpp"
#include "shared/fast_math.hpp"
extern double const unknown_facing_scale_79b628;
extern double const unknown_facing_origin_79b630;
// @ref ?unknown_facing_scale_79b628@@3NB=0079b628
// @ref ?unknown_facing_origin_79b630@@3NB=0079b630
// @ref ?Fast_Atan2@@YAMNN@Z=004ba600
UnknownFacingDir::UnknownFacingDir(CoordStruct const &from,CoordStruct const &to)
{
    if(from.X==to.X && from.Y==to.Y) Raw=0;
    *this=UnknownFacingDir((unsigned short)(int)((Fast_Atan2(double(from.Y)-to.Y,
        double(to.X)-from.X)-unknown_facing_origin_79b630)*unknown_facing_scale_79b628));
}
