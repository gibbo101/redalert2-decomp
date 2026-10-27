#include "shared/techno.hpp"
void UnknownTimed::unknown_496bc0(double time)
{
    if (IsActive || IsReverse != false) {
        time *= 900.0;
        IsActive = true;
        FrameDuration = time;
        Timer = UnknownDurationTimer423F60((long)time);
        IsReverse = false;
    }
}
