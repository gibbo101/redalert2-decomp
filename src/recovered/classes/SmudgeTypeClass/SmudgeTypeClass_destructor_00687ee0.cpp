// SmudgeTypeClass::~SmudgeTypeClass() (0x00687EE0)
// Leaves the notice lists and SmudgeTypes.
#include "shared/smudge_type.hpp"
// @ref ?Unknown_006ECB90@@YIXPAVAbstractClass@@_N@Z=006ecb90
// @ref ??1ObjectTypeClass@@UAE@XZ=005d5b60

SmudgeTypeClass::~SmudgeTypeClass()
{
    Unknown_006ECB90((ObjectClass *)(AbstractClass *)this, true);
    SmudgeTypes.Delete(this);
}
