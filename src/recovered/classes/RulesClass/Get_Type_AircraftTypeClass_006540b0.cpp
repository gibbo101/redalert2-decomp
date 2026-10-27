// Get_Type<AircraftTypeClass> (0x006540B0): the out-of-line copy of shared/ccini_class.hpp's
// Get_Type template that the Rules unit's readers call once their inline budget is spent.
#include "shared/ccini_class.hpp"
#include "shared/aircraft_type.hpp"

template AircraftTypeClass *__fastcall Get_Type<AircraftTypeClass>(CCINIClass &ini, char const *section, char const *entry, AircraftTypeClass *defvalue);
