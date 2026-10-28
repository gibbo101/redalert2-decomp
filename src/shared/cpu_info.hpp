// CPU and timer queries used to scale timings to the machine (declarations
// only; Get_CPU_Info is accepted in src/recovered/unowned/).
#ifndef RA2_SHARED_CPU_INFO_HPP
#define RA2_SHARED_CPU_INFO_HPP

// Runs the CPUID probes: the family (5 Pentium, 6 Pentium Pro and later),
// whether CPUID exists and, with text, the unavailable-feature text
// (0x004D2A20).
void __fastcall Get_CPU_Info(int *family, unsigned char *has_cpuid, char *text, unsigned int size);

// The performance counter frequency: returns its low dword and stores the
// high dword in high (0x005ABF20; QueryPerformanceFrequency).
unsigned int __fastcall Performance_Frequency_005abf20(unsigned int *high);

// Scenario.cpp's delay scaling constants (0x007A9208 0.8 for a Pentium Pro
// or later, 0x007A9210 200.0; data of that unit, not shared literals).
extern double const unknown_cpu_delay_scale_7a9208;
extern double const unknown_cpu_delay_factor_7a9210;

#endif
