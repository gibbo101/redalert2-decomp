#include "shared/techno.hpp"
bool UnknownTimed::Is_Complete_00496AD0() const
{
    if (IsActive && Timer.TotalTime) {
        if ((double)(Timer.TotalTime - Timer.Value()) / Timer.TotalTime != 1.0) return false;
    }
    return true;
}
