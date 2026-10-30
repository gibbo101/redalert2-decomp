#include "shared/unknown_map_generator.hpp"
#include "shared/fast_math.hpp"
#include "shared/random2.hpp"
#include "shared/crt_math.hpp"
extern Random2Class unknown_map_random_a705c0;
extern double const angle_half_pi_79b630,angle_pi_79d158,angle_turn_79c9b8;
extern double const angle_weight_7a5cd0,jitter_weight_7a5cc8,random_unit_7a5dd0;
// @ref ?angle_half_pi_79b630@@=0079b630
// @ref ?angle_pi_79d158@@=0079d158
// @ref ?angle_turn_79c9b8@@=0079c9b8
// @ref ?angle_weight_7a5cd0@@=007a5cd0
// @ref ?jitter_weight_7a5cc8@@=007a5cc8
// @ref ?random_unit_7a5dd0@@=007a5dd0
// @ref ?unknown_map_random_a705c0@@=00a705c0
// @ref ??RRandom2Class@@QAEHXZ=00638840
// Source ownership follows the generator's repeated angular operation; ECX is unused, RET16/ST0 are physical.
double UnknownMapGenerator::Angle_Score_00582970(Cell const &from,Cell const &to,double heading)
{
    int dx=(int)to.X-(int)from.X;
    int dy=(int)to.Y-(int)from.Y;
    double angle=dx!=0 ? Fast_Atan(-((double)dy/(double)dx)) : angle_half_pi_79b630;
    if(dx<0)angle+=angle_pi_79d158;
    heading=fabs(angle-heading);
    while(heading>=angle_turn_79c9b8)heading-=angle_turn_79c9b8;
    if(heading>angle_pi_79d158)heading=angle_turn_79c9b8-heading;
    return angle_weight_7a5cd0*heading+(unsigned)unknown_map_random_a705c0()*jitter_weight_7a5cc8*random_unit_7a5dd0;
}
