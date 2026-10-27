// CPU identification (0x004D2A20): runs the original handwritten CPUID probes,
// then reports the family byte and copies the unavailable-feature text.
#include "shared/ghidra_types.hpp"

// @ref ?unknown_cpu_probe_77f14d@@YAEXZ=0077f14d
// @ref ?unknown_cpu_family_probe_77f20f@@YAXXZ=0077f20f
// @ref ?unknown_cpu_family_8015a3@@3DA=008015a3
// @ref ?unknown_cpu_text_8015a5@@3PADA=008015a5
// @ref _strncpy=007823d0

extern unsigned char unknown_cpu_probe_77f14d();
extern void unknown_cpu_family_probe_77f20f();
extern char unknown_cpu_family_8015a3;
extern char unknown_cpu_text_8015a5[];
extern "C" char *__cdecl strncpy(char *, const char *, unsigned int);

void __fastcall Get_CPU_Info(int *family, unsigned char *has_cpuid, char *text, unsigned int size)
{
    *has_cpuid = unknown_cpu_probe_77f14d();
    unknown_cpu_family_probe_77f20f();
    *family = unknown_cpu_family_8015a3;
    if (text != 0) {
        strncpy(text, unknown_cpu_text_8015a5, size);
    }
}
