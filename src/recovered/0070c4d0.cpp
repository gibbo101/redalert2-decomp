// void UnitTrackerClass::Set_Unit_Count(int count) -- 0x0070C4D0
// Clears every entry, then limits the tracked types to count.
#include "shared/unit_tracker.hpp"

void UnitTrackerClass::Set_Unit_Count(int count)
{
    UnitCount = 512;
    Clear_Unit_Total();
    UnitCount = count;
}
