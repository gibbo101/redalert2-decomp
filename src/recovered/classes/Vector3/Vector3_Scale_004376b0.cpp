#include "shared/vector3.hpp"
Vector3 &Vector3::Scale_004376b0(float factor)
{
    X = factor * X; Y = factor * Y; Z = factor * Z;
    return *this;
}
