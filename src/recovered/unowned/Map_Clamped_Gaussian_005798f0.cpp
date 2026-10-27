#include "shared/map_gaussian.hpp"
// @ref ?Next@MapGaussianClass@@QAENXZ=00579830
// @ref ?unknown_map_gaussian_a6fd50@@3VMapGaussianClass@@A=00a6fd50
double __stdcall Map_Clamped_Gaussian_005798f0(double mean,double deviation,double minimum,double maximum)
{
    if(maximum<mean-deviation || mean+deviation<minimum) {
        deviation=(maximum-minimum)*0.5;
        mean=deviation+minimum;
    }
    double value;
    do {
        value=unknown_map_gaussian_a6fd50.Next()*deviation+mean;
    } while(value<minimum || value>maximum);
    return value;
}
