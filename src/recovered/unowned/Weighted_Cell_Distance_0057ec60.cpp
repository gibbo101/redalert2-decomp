// Weighted cell-distance search key (TibSun MapGeneratorClass::Get_Spread_Score); name/stdcall/free/return
// precision are hypotheses. The random term is the inlined Map_Random_Fraction_00579770 callback.
#include "shared/coord.hpp"
#include "shared/random2.hpp"
#include "shared/fast_math.hpp"
extern float const unknown_distance_scale_7a5c9c,unknown_jitter_scale_7a5ca0,unknown_weight_scale_7a5ca4;
// @ref ?unknown_distance_scale_7a5c9c@@=007a5c9c
// @ref ?unknown_jitter_scale_7a5ca0@@=007a5ca0
// @ref ?unknown_weight_scale_7a5ca4@@=007a5ca4
// @ref ?Fast_Sqrt@@YAMN@Z=004ba410
// @ref ??RRandom2Class@@QAEHXZ=00638840
// @ref ?unknown_map_random_a705c0@@3VRandom2Class@@A=00a705c0
// @ref __real@8@3fdf8000000080000000=007a5dd0
double __cdecl Map_Random_Fraction_00579770();
double __stdcall Weighted_Cell_Distance_0057ec60(Cell const *from,Cell const *to,int weight)
{
    int dx=(int)from->X-(int)to->X;
    int dy=(int)from->Y-(int)to->Y;
    int squared=(int)((unsigned)dy*(unsigned)dy+(unsigned)dx*(unsigned)dx);
    float distance=Fast_Sqrt((double)squared);
    return unknown_jitter_scale_7a5ca0*Map_Random_Fraction_00579770()+distance*unknown_distance_scale_7a5c9c-weight*unknown_weight_scale_7a5ca4;
}
