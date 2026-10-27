// ObjectClass::ObjectClass(NoInitClass const &noinit) (0x005D2500)
#include "shared/object_type.hpp"
// @ref ??0AbstractClass@@QAE@ABVNoInitClass@@@Z=0040ff60
// @ref ??_7ObjectClass@@6BIPersistStream@@@=007a7498
// @ref ??_7ObjectClass@@6BIRTTITypeInfo@@@=007a747c
// @ref ??_7ObjectClass@@6BINoticeSink@@@=007a7474
// @ref ??_7ObjectClass@@6BINoticeSource@@@=007a746c

ObjectClass::ObjectClass(NoInitClass const &noinit) :
    AbstractClass(noinit),
    unknown_24(noinit)
{
}
