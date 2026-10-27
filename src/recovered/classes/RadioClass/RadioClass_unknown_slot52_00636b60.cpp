// bool RadioClass::unknown_slot52() (0x00636B60, slot 52)
// Sends message 3 to every contact first unless unknown_76 is set.
#include "shared/radio.hpp"
// @ref ?unknown_slot52@ObjectClass@@UAE_NXZ=005d3700

bool RadioClass::unknown_slot52()
{
    if (!unknown_76) {
        unknown_slot152(3);
    }
    return ObjectClass::unknown_slot52();
}
