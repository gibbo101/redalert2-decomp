// ScriptClass::~ScriptClass() (0x006687D0)
// Releases references to the script and removes it from Scripts.
#include "shared/script.hpp"
// @ref ??1AbstractClass@@UAE@XZ=0040ff90
// @ref ?Unknown_006ECB90@@YIXPAVAbstractClass@@_N@Z=006ecb90

ScriptClass::~ScriptClass()
{
    Unknown_006ECB90(this, true);
    Scripts.Delete(this);
}
