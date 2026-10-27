#include "shared/facing.hpp"
UnknownFacingDir FacingClass::Difference_To_Desired() const
{
    UnknownFacingDir current = Current();
    UnknownFacingDir desired = *(UnknownFacingDir const *)&Desired;
    return UnknownFacingDir((unsigned short)(desired.Raw - current.Raw));
}
