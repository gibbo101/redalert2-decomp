// void UnitTrackerClass::Clear_Unit_Total() -- 0x0070C540
#include "shared/unit_tracker.hpp"

void UnitTrackerClass::Clear_Unit_Total()
{
    for (int index = 0; index < UnitCount; index++) {
        UnitTotals[index] = 0;
    }
}
