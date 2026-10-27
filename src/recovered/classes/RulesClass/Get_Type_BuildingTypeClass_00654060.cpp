// Get_Type<BuildingTypeClass> (0x00654060): the out-of-line copy of shared/ccini_class.hpp's
// Get_Type template that the Rules unit's readers call once their inline budget is spent.
#include "shared/ccini_class.hpp"
#include "shared/building_type.hpp"

template BuildingTypeClass *__fastcall Get_Type<BuildingTypeClass>(CCINIClass &ini, char const *section, char const *entry, BuildingTypeClass *defvalue);
