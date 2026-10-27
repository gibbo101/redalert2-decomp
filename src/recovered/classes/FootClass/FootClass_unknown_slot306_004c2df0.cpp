// void FootClass::unknown_slot306(double value) (0x004C2DF0)
// Stores a factor clamped to 0..1 (hypothesis: the unit's speed fraction).
#include "shared/foot.hpp"
// @ref __real@8@3fff8000000000000000=0079a708
// @ref __real@8@00000000000000000000=0079b610

template <class T>
inline T Unknown_Clamp(T const &value, T const &low, T const &high)
{
    if (value >= high) {
        return high;
    }
    if (value <= low) {
        return low;
    }
    return value;
}

void FootClass::unknown_slot306(double value)
{
    unknown_468 = Unknown_Clamp(value, 0.0, 1.0);
}
