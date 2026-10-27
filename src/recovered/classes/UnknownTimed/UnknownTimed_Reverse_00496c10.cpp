#include "shared/techno.hpp"
void UnknownTimed::Reverse_00496C10()
{
    if (IsActive) {
        Timer.Reverse();
        IsReverse = !IsReverse;
    }
}
