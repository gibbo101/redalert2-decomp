// UnitTrackerClass::UnitTrackerClass() -- 0x0070C440
#include "shared/unit_tracker.hpp"

UnitTrackerClass::UnitTrackerClass()
{
    UnitCount = 512;
    Clear_Unit_Total();
    InNetworkFormat = 0;
}
