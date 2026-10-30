#include "shared/coord.hpp"
#include "shared/random2.hpp"
#include "shared/unknown_geometry.hpp"
extern Random2Class unknown_map_random_a705c0;
// @ref ?unknown_map_random_a705c0@@=00a705c0
// @ref ??RRandom2Class@@QAEHXZ=00638840
extern double const unknown_random_scale_7a5dd0;
// @ref ?unknown_random_scale_7a5dd0@@=007a5dd0
extern double const unknown_distance_scale_007a5cf8;
// @ref ?unknown_distance_scale_007a5cf8@@=007a5cf8
double __stdcall Randomized_Cell_Distance_005846b0(Cell const &a,Cell const &b)
{
    int dx=(int)a.X-(int)b.X;
    int dy=(int)a.Y-(int)b.Y;
    int square=(int)((unsigned)dy*(unsigned)dy+(unsigned)dx*(unsigned)dx);
    double distance=unknown_sqrt_4ba410((double)square);
    return distance+(unsigned int)unknown_map_random_a705c0()*unknown_random_scale_7a5dd0*unknown_distance_scale_007a5cf8;
}
