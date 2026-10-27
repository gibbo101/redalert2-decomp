// void MonoClass::Printf(char const *format, ...) (0x0059E7F0)
#include "shared/mono_class.hpp"
// @ref ?unknown_mono_enabled_a70f0a@@3_NA=00a70f0a
// @ref ?Print@MonoClass@@QAEXPBD@Z=0059e6d0
// @ref _vsprintf=007849ba

void MonoClass::Printf(char const *format, ...)
{
    if (unknown_mono_enabled_a70f0a) {
        char buffer[256];
        vsprintf(buffer, format, (char *)(&format + 1));
        buffer[255] = 0;
        Print(buffer);
    }
}
