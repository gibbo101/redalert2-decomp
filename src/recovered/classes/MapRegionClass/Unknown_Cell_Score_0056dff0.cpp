// double __stdcall Unknown_Cell_Score_0056dff0(Cell const &from, Cell const &to, double direction) (0x0056DFF0):
// a random-weighted score for the step from -> to: 0.15 * distance + 1.5 * the angle between the step's direction
// (atan of -dy/dx, +pi for negative dx, pi/2 when dx is 0) and direction (folded into [0, pi]) + 2.5 * a random
// fraction. The three weights are double constants in .rdata (0x007A5BE0-0x007A5BF0), not __real literals.
#include "shared/coord.hpp"
#include "shared/random2.hpp"
#include "shared/unknown_geometry.hpp"
#include "shared/crt_math.hpp"
// @ref ?unknown_map_random_a705c0@@3VRandom2Class@@A=00a705c0
// @ref ??RRandom2Class@@QAEHXZ=00638840
// @ref ?unknown_sqrt_4ba410@@YANN@Z=004ba410
// @ref ?unknown_math_4ba5b0@@YANN@Z=004ba5b0
#include "shared/map_random.hpp"
// @ref ?unknown_weight_random_7a5be0@@3NB=007a5be0
// @ref ?unknown_weight_distance_7a5be8@@3NB=007a5be8
// @ref ?unknown_weight_angle_7a5bf0@@3NB=007a5bf0
extern const double unknown_weight_random_7a5be0;      // 0x007A5BE0 2.5
extern const double unknown_weight_distance_7a5be8;    // 0x007A5BE8 0.15
extern const double unknown_weight_angle_7a5bf0;       // 0x007A5BF0 1.5

double __stdcall Unknown_Cell_Score_0056dff0(Cell const &from, Cell const &to, double direction)
{
    int dx = to.X - from.X;
    int dy = to.Y - from.Y;
    double distance = unknown_sqrt_4ba410((double)(dy * dy + dx * dx));
    double angle = dx ? unknown_math_4ba5b0(-((double)dy / (double)dx)) : 1.5707963267948966;
    if (dx < 0) {
        angle += 3.141592653589793;
    }
    angle = fabs(angle - direction);
    while (angle >= 6.283185307179586) {
        angle -= 6.283185307179586;
    }
    if (angle > 3.141592653589793) {
        angle = 6.283185307179586 - angle;
    }
    return unknown_weight_distance_7a5be8 * distance + unknown_weight_angle_7a5bf0 * angle + ((unsigned int)unknown_map_random_a705c0() * (1.0 / 4294967295.0)) * unknown_weight_random_7a5be0;
}
