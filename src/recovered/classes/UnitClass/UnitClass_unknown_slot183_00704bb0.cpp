// UnknownFacingDir UnitClass::unknown_slot183() (0x00704BB0, slot 183)
// The turret's current facing for a turreted type, otherwise the techno's.
#include "shared/unit.hpp"
// @ref ?Current@FacingClass@@QBE?AUUnknownFacingDir@@XZ=004b8be0
// @ref ?unknown_slot183@TechnoClass@@UAE?AUUnknownFacingDir@@XZ=006d3f80

UnknownFacingDir UnitClass::unknown_slot183()
{
    if (Type->Turret) {
        return unknown_2f8.Current();
    }
    return TechnoClass::unknown_slot183();
}
