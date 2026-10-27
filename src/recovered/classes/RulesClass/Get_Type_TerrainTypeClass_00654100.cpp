// Get_Type<TerrainTypeClass> (0x00654100): the out-of-line copy of shared/ccini_class.hpp's
// Get_Type template that the Rules unit's readers call once their inline budget is spent.
#include "shared/ccini_class.hpp"
#include "shared/terrain_type.hpp"

template TerrainTypeClass *__fastcall Get_Type<TerrainTypeClass>(CCINIClass &ini, char const *section, char const *entry, TerrainTypeClass *defvalue);
