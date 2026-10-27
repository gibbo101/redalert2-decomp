// bool BuildingClass::unknown_slot195() (0x00450360, slot 195)
// Whether the building is operating: it is on (unknown_530) or has two
// occupants, is not disabled (unknown_3fc), has strength, is not a Powered
// toggling type on a low-power house without two occupants, and, for an
// engineer-captured type, is held (unknown_59c).
#include "shared/building.hpp"
#include "shared/house.hpp"
// @ref ?Power_Fraction@HouseClass@@QBENXZ=004e8330

bool BuildingClass::unknown_slot195()
{
    if (!unknown_530 && unknown_53c.Count() < 2) {
        return false;
    }
    if (unknown_3fc > 0) {
        return false;
    }
    if (!Strength) {
        return false;
    }
    if (Type->Powered && Type->PowerDrain_c6c > 0 && Type->TogglePower) {
        if (House->Power_Fraction() < 1.0 && unknown_53c.Count() < 2) {
            return false;
        }
    }
    if (Type->NeedsEngineer && !unknown_59c) {
        return false;
    }
    return true;
}
