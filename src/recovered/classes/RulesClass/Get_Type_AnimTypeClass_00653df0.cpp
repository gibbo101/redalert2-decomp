// Get_Type<AnimTypeClass> (0x00653DF0): the out-of-line copy of shared/ccini_class.hpp's
// Get_Type template that RulesClass::Audio_Visual (0x00643E10) calls once its inline budget is spent.
#include "shared/ccini_class.hpp"
#include "shared/anim_type.hpp"

template AnimTypeClass *__fastcall Get_Type<AnimTypeClass>(CCINIClass &ini, char const *section, char const *entry, AnimTypeClass *defvalue);
