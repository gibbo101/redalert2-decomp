// ScriptTypeClass::~ScriptTypeClass() (0x00668AE0)
// Releases references to the type and removes it from ScriptTypes.
#include "shared/script.hpp"
// @ref ??1AbstractTypeClass@@UAE@XZ=00410740
// @ref ?Unknown_006ECB90@@YIXPAVAbstractClass@@_N@Z=006ecb90

ScriptTypeClass::~ScriptTypeClass()
{
    Unknown_006ECB90(this, true);
    ScriptTypes.Delete(this);
}
