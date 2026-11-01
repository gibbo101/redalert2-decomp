// void UnitTrackerClass::To_PC_Format() -- 0x0070C5C0
// Byte-swaps every count back to host order once.
// @ref _ntohl@4=00781b72
#include "shared/unit_tracker.hpp"

extern "C" unsigned long __stdcall ntohl(unsigned long value);

void UnitTrackerClass::To_PC_Format()
{
    if (InNetworkFormat) {
        for (int index = 0; index < UnitCount; index++) {
            UnitTotals[index] = ntohl(UnitTotals[index]);
        }
    }
    InNetworkFormat = 0;
}
