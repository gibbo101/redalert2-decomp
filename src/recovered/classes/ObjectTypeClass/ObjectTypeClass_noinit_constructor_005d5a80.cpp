// ObjectTypeClass::ObjectTypeClass(NoInitClass const &noinit) (0x005D5A80)
// Load path: only the members with constructors of their own are set up.
#include "shared/object_type.hpp"
// @ref ??0AbstractTypeClass@@QAE@ABVNoInitClass@@@Z=004106e0
// @ref ??_7ObjectTypeClass@@6BIPersistStream@@@=007a76f8
// @ref ??_7ObjectTypeClass@@6BIRTTITypeInfo@@@=007a76dc
// @ref ??_7ObjectTypeClass@@6BINoticeSink@@@=007a76d4
// @ref ??_7ObjectTypeClass@@6BINoticeSource@@@=007a76cc

ObjectTypeClass::ObjectTypeClass(NoInitClass const &noinit) :
    AbstractTypeClass(noinit),
    RadialColor(noinit),
    unknown_a4(0),
    unknown_b0(noinit),
    unknown_b8(noinit),
    unknown_c0(noinit),
    unknown_1c8(noinit),
    unknown_1e3(noinit),
    LineTrailColor(noinit)
{
}
