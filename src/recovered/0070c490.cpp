// void UnitTrackerClass::Increment_Unit_Total(int unit_type) -- 0x0070C490
#include "shared/unit_tracker.hpp"

void UnitTrackerClass::Increment_Unit_Total(int unit_type)
{
    if (unit_type < UnitCount) {
        UnitTotals[unit_type]++;
    }
}
