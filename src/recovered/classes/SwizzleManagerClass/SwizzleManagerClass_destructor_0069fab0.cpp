// SwizzleManagerClass::~SwizzleManagerClass() (0x0069FAB0)
// Resolves what is still pending.
#include "shared/swizzle.hpp"

// @ref ?Process_Tables@SwizzleManagerClass@@AAEXXZ=0069fc30

SwizzleManagerClass::~SwizzleManagerClass()
{
    Process_Tables();
}
