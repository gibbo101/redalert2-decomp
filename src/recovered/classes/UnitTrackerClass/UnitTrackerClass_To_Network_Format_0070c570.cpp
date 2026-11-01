// void UnitTrackerClass::To_Network_Format() -- 0x0070C570
// Byte-swaps every count to network order once.
// @ref _htonl@4=00781b66
#include "shared/unit_tracker.hpp"

extern "C" unsigned long __stdcall htonl(unsigned long value);

void UnitTrackerClass::To_Network_Format()
{
    if (!InNetworkFormat) {
        for (int index = 0; index < UnitCount; index++) {
            UnitTotals[index] = htonl(UnitTotals[index]);
        }
    }
    InNetworkFormat = 1;
}
