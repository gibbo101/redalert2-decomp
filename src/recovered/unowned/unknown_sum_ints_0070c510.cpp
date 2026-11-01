// int UnitTrackerClass::Get_All_Totals_Sum() -- 0x0070C510
#include "shared/unit_tracker.hpp"

int UnitTrackerClass::Get_All_Totals_Sum()
{
    int total = 0;
    for (int index = 0; index < UnitCount; index++) {
        total += UnitTotals[index];
    }
    return total;
}
