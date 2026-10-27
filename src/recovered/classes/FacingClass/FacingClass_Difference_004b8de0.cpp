#include "shared/facing.hpp"
UnknownFacingDir FacingClass::Difference(UnknownFacingDir const &dir) const
{
    return UnknownFacingDir((unsigned short)(dir.Raw - Current().Raw));
}
