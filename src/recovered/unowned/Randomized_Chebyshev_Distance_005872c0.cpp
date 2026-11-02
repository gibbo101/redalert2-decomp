#include "shared/coord.hpp"
#include "shared/random2.hpp"
#include "shared/map_random.hpp"
// @ref ?unknown_map_random_a705c0@@=00a705c0
// @ref ??RRandom2Class@@QAEHXZ=00638840
#include "shared/crt_memory.hpp"
extern double unknown_distance_scale_7a5d50;
extern double const unknown_random_scale_7a5dd0;
// @ref ?unknown_distance_scale_7a5d50@@=007a5d50
// @ref ?unknown_random_scale_7a5dd0@@=007a5dd0
double __stdcall Randomized_Chebyshev_Distance_005872c0(Cell const &a,Cell const &b)
{
    int x = (int)a.X - (int)b.X;
    int y = (int)a.Y - (int)b.Y;
    double distance=abs(x)>abs(y)?abs(x):abs(y);
    return distance + (unsigned int)unknown_map_random_a705c0()*unknown_random_scale_7a5dd0*unknown_distance_scale_7a5d50;
}
