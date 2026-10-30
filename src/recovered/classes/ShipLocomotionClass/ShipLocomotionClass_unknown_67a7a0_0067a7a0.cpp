// bool ShipLocomotionClass::unknown_67a7a0() (0x0067A7A0)
// With nothing in the unit's 0x478 list: slot 260 (0, 1) and false; else
// 0x004CD9B0 and slot 261 (false, true). Unreferenced.
#include "shared/ship_locomotion.hpp"
#include "shared/vector_class.hpp"

bool ShipLocomotionClass::unknown_67a7a0()
{
    if (LinkedTo->unknown_478.Count() == 0) {
        LinkedTo->unknown_slot260(0, 1);
        return false;
    }
    LinkedTo->unknown_4cd9b0();
    return LinkedTo->unknown_slot261(false, true);
}
