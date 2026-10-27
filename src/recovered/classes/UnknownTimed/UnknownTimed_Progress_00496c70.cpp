#include "shared/techno.hpp"
double UnknownTimed::Progress_00496C70() const
{
    if (IsActive) {
        return Timer.Percentage();
    }
    return 1.0;
}
