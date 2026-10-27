#include "shared/facing.hpp"
#include "shared/crt_memory.hpp"
// Original member name and const spelling remain source hypotheses.
bool UnknownFacingDir::Magnitude_At_Least_004bfb30(UnknownFacingDir const &other) const
{
    return abs((short)Raw)>=abs((short)other.Raw);
}
