#include "shared/vector3.hpp"
Vector3 &Vector3::Add_004376e0(Vector3 const &other)
{
    X = other.X + X; Y = other.Y + Y; Z = other.Z + Z;
    return *this;
}
