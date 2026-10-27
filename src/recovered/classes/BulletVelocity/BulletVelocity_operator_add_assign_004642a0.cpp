// Existing three-double vector operation; original4642A0 full33+15.
#include "shared/bullet.hpp"

// The existing shared vector operation, with an ordinary out-of-class definition.
// No alias, inlining pragma, auxiliary operation, or forced call is introduced.
BulletVelocity &BulletVelocity::operator+=(BulletVelocity const &other)
{
    X+=other.X;
    Y+=other.Y;
    Z+=other.Z;
    return *this;
}
