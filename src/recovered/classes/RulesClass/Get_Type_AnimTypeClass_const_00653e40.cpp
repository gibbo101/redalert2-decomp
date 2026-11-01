// Get_Type<AnimTypeClass const> (0x00653E40): a second instantiation of shared/ccini_class.hpp's
// Get_Type template, byte-identical to 0x00653DF0, for the const anim fields RulesClass::Audio_Visual
// (0x00643E10) reads (EMPulseSparkles +0x1438, OreTwinkle +0x14B8; TibSun types Rules anims const).
#include "shared/ccini_class.hpp"
#include "shared/anim_type.hpp"

template AnimTypeClass const *__fastcall Get_Type<AnimTypeClass const>(CCINIClass &ini, char const *section, char const *entry, AnimTypeClass const *defvalue);
