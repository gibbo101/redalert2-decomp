// int UnitClass::unknown_slot166() (0x00704A20, slot 166)
// With pip scale 2 (tiberium) the pips to show: the stored total over the
// type's Storage times the type's pip count (slot 29), rounded; otherwise
// the techno's answer.
#include "shared/unit.hpp"
// @ref ?unknown_slot166@TechnoClass@@UAEHXZ=006d3ed0
// @ref ?Get_Total_Amount@StorageClass@@QBEMXZ=0069ae10
// @ref __ftol=0077f110

int UnitClass::unknown_slot166()
{
    switch (Type->PipScale) {
    case 2:
    {
        double ratio = unknown_294.Get_Total_Amount() / Type->Storage;
        return (int)(Type->unknown_slot29() * ratio + 0.5);
    }
    }
    return TechnoClass::unknown_slot166();
}
