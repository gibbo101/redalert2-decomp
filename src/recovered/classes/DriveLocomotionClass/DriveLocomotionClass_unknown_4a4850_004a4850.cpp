// bool DriveLocomotionClass::unknown_4a4850() (0x004A4850)
// With nothing in the unit's 0x478 list: slot 260 (0, 1) and false; else
// 0x004CD9B0 and slot 261 (false, true). Unreferenced.
#include "shared/drive_locomotion.hpp"
#include "shared/vector_class.hpp"

bool DriveLocomotionClass::unknown_4a4850()
{
    if (LinkedTo->unknown_478.Count() == 0) {
        LinkedTo->unknown_slot260(0, 1);
        return false;
    }
    LinkedTo->unknown_4cd9b0();
    return LinkedTo->unknown_slot261(false, true);
}
