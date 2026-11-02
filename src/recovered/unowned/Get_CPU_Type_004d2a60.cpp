// int Get_CPU_Type() (0x004D2A60): the CPU type index from the CPUID family and model and the
// vendor text (Get_CPU_Info inlined): -1 unknown, 0 486, 1 Pentium, 2 Pentium Pro, 3 Pentium II,
// 4 Pentium III, 5 Celeron, 6 Pentium 4, 7 AMD, 8 Cyrix (the names table 0x007D8838).
#include "shared/cpu_info.hpp"
#include "shared/crt_string.hpp"

// @ref ?unknown_cpu_model_8015a4@@3DA=008015a4
// @ref __stricmp=00781f20
// @ref ??_C@_0N@OLMF@AuthenticAMD?$AA@=007d88bc
// @ref ??_C@_0N@MOOL@CyrixInstead?$AA@=007d88ac

extern char unknown_cpu_model_8015a4;

int Get_CPU_Type()
{
    int family;
    unsigned char has_cpuid;
    char vendor[64];
    Get_CPU_Info(&family, &has_cpuid, vendor, sizeof(vendor));
    if (family == 0 || unknown_cpu_model_8015a4 == 0) {
        return -1;
    }
    if (_stricmp(vendor, "AuthenticAMD") == 0) {
        return 7;
    }
    if (_stricmp(vendor, "CyrixInstead") == 0) {
        return 8;
    }
    switch (family) {
    case 4:
        return 0;
    case 5:
        return 1;
    case 6:
        switch (unknown_cpu_model_8015a4) {
        case 3:
        case 5:
            return 3;
        case 6:
            return 5;
        case 7:
        case 8:
        case 10:
            return 4;
        default:
            return 2;
        }
    default:
        return 6;
    }
}
