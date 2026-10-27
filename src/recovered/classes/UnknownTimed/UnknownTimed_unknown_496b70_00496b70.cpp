#include "shared/techno.hpp"
void UnknownTimed::unknown_496b70(double time)
{
    if (IsActive || IsReverse != true) {
        time *= 900.0;
        IsActive = true;
        FrameDuration = time;
        Timer = UnknownDurationTimer423F60((long)time);
        IsReverse = true;
    }
}
