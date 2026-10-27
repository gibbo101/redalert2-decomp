// Original local-double-vector XY length0041B750; free/member identity is a hypothesis.
#include "shared/aircraft_vector_xy.hpp"
#include "shared/unknown_geometry.hpp"
double __fastcall Aircraft_XY_Length_0041B750(AircraftVectorXY const *vector)
{
    double y = vector->Y;
    double x = vector->X;
    return unknown_sqrt_4ba410(x * x + y * y);
}
