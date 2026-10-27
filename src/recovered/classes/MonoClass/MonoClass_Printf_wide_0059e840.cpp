// void MonoClass::Printf(wchar_t const *format, ...) (0x0059E840)
#include "shared/mono_class.hpp"
// @ref ??_C@_02GKFL@?$CFS?$AA@=007e2af0
// @ref ?unknown_mono_enabled_a70f0a@@3_NA=00a70f0a
// @ref ?Print@MonoClass@@QAEXPBD@Z=0059e6d0
// @ref _vswprintf=00783a58
// @ref _sprintf=007820f4

void MonoClass::Printf(wchar_t const *format, ...)
{
    if (unknown_mono_enabled_a70f0a) {
        wchar_t wide[256];
        char buffer[256];
        vswprintf(wide, format, (char *)(&format + 1));
        sprintf(buffer, "%S", wide);
        Print(buffer);
    }
}
