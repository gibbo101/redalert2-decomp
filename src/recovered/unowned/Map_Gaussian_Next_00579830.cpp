#include "shared/map_gaussian.hpp"
extern "C" double __cdecl log(double);
#pragma intrinsic(log)
double __cdecl unknown_sqrt_4ba410(double);
// @ref ?unknown_sqrt_4ba410@@YANN@Z=004ba410
double MapGaussianClass::Next()
{
    if(HasSpare) {
        HasSpare=false;
        return Spare;
    }
    double x,y,radius;
    do {
        x=2.0*Uniform()-1.0;
        y=2.0*Uniform()-1.0;
        radius=x*x+y*y;
    } while(radius>=1.0 || radius==0.0);
    double scale=unknown_sqrt_4ba410((-log(radius)-log(radius))/radius);
    HasSpare=true;
    Spare=y*scale;
    return x*scale;
}
