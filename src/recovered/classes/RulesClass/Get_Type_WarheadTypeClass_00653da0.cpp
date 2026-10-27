// Get_Type<WarheadTypeClass> (0x00653DA0): the out-of-line copy of shared/ccini_class.hpp's
// Get_Type template that the Rules unit's readers call once their inline budget is spent.
#include "shared/ccini_class.hpp"
#include "shared/warhead_type.hpp"

template WarheadTypeClass *__fastcall Get_Type<WarheadTypeClass>(CCINIClass &ini, char const *section, char const *entry, WarheadTypeClass *defvalue);
