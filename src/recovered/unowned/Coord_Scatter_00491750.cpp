#include "shared/coord.hpp"
#include "shared/abstract.hpp"
#include "shared/random.hpp"
#include "shared/techno.hpp"
#include "shared/fast_math.hpp"
#include "shared/unknown_vector3.hpp"
extern double const unknown_facing_radians_79b620;
// @ref ?unknown_facing_radians_79b620@@3NB=0079b620
// @ref ?Fast_Sin@@YAMN@Z=004ba480
// @ref ?Fast_Cos@@YAMN@Z=004ba4d0
// @ref ??0UnknownVector3@@QAE@HHH@Z=0041b630
// Actual three-component position, preserving the out-of-line vector constructor.
inline UnknownVector3 Compute_Scatter_Vector(CoordStruct const &coord,double radians,int distance)
{
    int x,y,z;
    z = coord.Z;
    y = (int)(coord.Y - (double)Fast_Sin(radians) * distance);
    x = (int)(coord.X + (double)Fast_Cos(radians) * distance);
    UnknownVector3 result(x,y,z);
    return result;
}
CoordStruct __fastcall Coord_Scatter(CoordStruct const &coord, int distance, bool lock)
{
    {
    UnknownFacingDir direction(0);
    unsigned direction_word = (*(unsigned *)&direction & 0xFFFF00FF) | ((unknown_id_source_a3d290->Random()() & 255) << 8);
    double radians = ((short)direction_word - 0x3FFF) * unknown_facing_radians_79b620;
    UnknownVector3 offset=Compute_Scatter_Vector(coord,radians,distance);
    CoordStruct result(offset.X,offset.Y,offset.Z);
    if ((unsigned)(result.X / 256) >= 512 || (unsigned)(result.Y / 256) >= 512) result = coord;
    if (lock) {
        result = result - CoordStruct(result.X & 255,result.Y & 255,0);
        result = result + CoordStruct(128,128,0);
    }
    return result;
}

}