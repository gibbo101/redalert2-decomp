// InfantryTypeClass::InfantryTypeClass(NoInitClass const &noinit) (0x00509D60)
// Load path.
#include "shared/infantry_type.hpp"
// @ref ??0TechnoTypeClass@@QAE@ABVNoInitClass@@@Z=006da6e0
// @ref ??_7?$TypeList@PAVAnimTypeClass@@@@6B@=007a3b3c
// @ref ??_7?$TypeList@H@@6B@=0079d9f4
// @ref ??_7InfantryTypeClass@@6BIPersistStream@@@=007a3a78
// @ref ??_7InfantryTypeClass@@6BIRTTITypeInfo@@@=007a3a5c
// @ref ??_7InfantryTypeClass@@6BINoticeSink@@@=007a3a54
// @ref ??_7InfantryTypeClass@@6BINoticeSource@@@=007a3a4c

InfantryTypeClass::InfantryTypeClass(NoInitClass const &noinit) :
    TechnoTypeClass(noinit),
    DeadBodies(noinit),
    DeathAnims(noinit),
    VoiceComment(noinit)
{
}
