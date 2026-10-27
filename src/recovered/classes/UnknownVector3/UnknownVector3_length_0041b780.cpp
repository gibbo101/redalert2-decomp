// Existing UnknownVector3 Euclidean length (0041B780), double intermediates then signed FTOL.
#include "shared/unknown_vector3.hpp"
#include "shared/unknown_geometry.hpp"
int UnknownVector3::Length() const
{
    double z = Z;
    double y = Y;
    double x = X;
    return (int)unknown_sqrt_4ba410(x * x + y * y + z * z);
}
