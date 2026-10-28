// Weighted cell-distance search key; name/stdcall/free/return precision are hypotheses.
#include "shared/coord.hpp"
#include "shared/random2.hpp"
#include "shared/fast_math.hpp"
extern Random2Class unknown_random_a705c0;
extern float const unknown_distance_scale_7a5c9c,unknown_jitter_scale_7a5ca0,unknown_weight_scale_7a5ca4;
extern double const unknown_random_unit_scale_7a5dd0;
// @ref ?unknown_random_a705c0@@=00a705c0
// @ref ?unknown_distance_scale_7a5c9c@@=007a5c9c
// @ref ?unknown_jitter_scale_7a5ca0@@=007a5ca0
// @ref ?unknown_weight_scale_7a5ca4@@=007a5ca4
// @ref ?unknown_random_unit_scale_7a5dd0@@=007a5dd0
// @ref ?Fast_Sqrt@@YAMN@Z=004ba410
// @ref ??RRandom2Class@@QAEHXZ=00638840
double __stdcall Weighted_Cell_Distance_0057ec60(Cell const *from,Cell const *to,int weight)
{
    int dx=(int)from->X-(int)to->X;
    int dy=(int)from->Y-(int)to->Y;
    int squared=(int)((unsigned)dy*(unsigned)dy+(unsigned)dx*(unsigned)dx);
    float distance=Fast_Sqrt((double)squared);
    unsigned int sample=(unsigned int)unknown_random_a705c0();
    double jitter=(double)sample*unknown_random_unit_scale_7a5dd0;
    jitter*=unknown_jitter_scale_7a5ca0;
    return (double)unknown_distance_scale_7a5c9c*distance+jitter-(float)weight*unknown_weight_scale_7a5ca4;
}
