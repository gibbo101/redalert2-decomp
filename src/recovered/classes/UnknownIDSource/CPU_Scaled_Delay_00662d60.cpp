// int __fastcall CPU_Scaled_Delay_00662d60(int delay) (0x00662D60)
// Scales a delay to the machine: 80% on a Pentium Pro or later (CPU family
// above 5), then delay * 200 / the performance counter frequency in MHz
// (name hypothesis).
// @ref ?Get_CPU_Info@@YIXPAHPAEPADI@Z=004d2a20
// @ref ?Performance_Frequency_005abf20@@YIIPAI@Z=005abf20
// @ref ?unknown_cpu_delay_scale_7a9208@@3NB=007a9208
// @ref ?unknown_cpu_delay_factor_7a9210@@3NB=007a9210
// @ref __real@8@401f8000000000000000=0079de10
// @ref __real@8@3feb8637bd05af6c6800=007a7d20
#include "shared/cpu_info.hpp"

int __fastcall CPU_Scaled_Delay_00662d60(int delay)
{
    int family;
    unsigned char has_cpuid;
    int mhz = 0;
    Get_CPU_Info(&family, &has_cpuid, 0, 0);
    if (family > 5) {
        delay = delay * unknown_cpu_delay_scale_7a9208;
    }
    unsigned int high;
    unsigned int low = Performance_Frequency_005abf20(&high);
    if (low != 0 || high != 0) {
        mhz = (high * 4294967296.0 + low) * 0.000001;
    }
    return delay * unknown_cpu_delay_factor_7a9210 / mhz;
}
