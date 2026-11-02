// MillisecondTimerClass (shared/milsectmr.hpp; Westwood's milsectmr.cpp as in the Tiberian Sun sources, unit 0x00593530-0x00593674):
// a millisecond clock from the time-stamp counter scaled by the performance counter frequency,
// or the multimedia timer (raised to 1 ms resolution) when no frequency is reported.
#include "shared/win32_api.hpp"
#include "shared/cpu_info.hpp"
#include "shared/bench.hpp"
#include "shared/debug_printf.hpp"
#include "shared/milsectmr.hpp"
// @ref __imp__timeBeginPeriod@4=0079a52c
// @ref __imp__timeEndPeriod@4=0079a520
// @ref __imp__timeGetTime@0=0079a524
// @ref ?Performance_Frequency_005abf20@@YIIPAI@Z=005abf20
// @ref ?Get_CPU_Info@@YIXPAHPAEPADI@Z=004d2a20
// @ref ?Get_CPU_Clock@@YAKAAK@Z=0077f274
// @ref ??_C@_0CL@PEMG@MillisecondTimerClass?5low?5?$DN?5?$CFd?0?5@=007e1d08
// @ref _?cpu_type@?1???BMillisecondTimerClass@@QBENXZ@4HA=007e1d04
// @ref _?has_mmx@?1???BMillisecondTimerClass@@QBENXZ@4_NA=00a70bcc
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
WIN32_IMPORT unsigned int WINAPI timeBeginPeriod(unsigned int period);
WIN32_IMPORT unsigned int WINAPI timeEndPeriod(unsigned int period);

#define LI_TO_DBL(dh, dl) ((double)((double)dh * 4.294967296E9 + (double)dl))



MillisecondTimerClass::MillisecondTimerClass()
{
    unsigned int high = 0;
    Frequency = 1.0;
    unsigned int low = Performance_Frequency_005abf20(&high);

    if (low == 0 && high == 0) {
        timeBeginPeriod(1);
    } else {
        double dl = low;
        double dh = high;

        Debug_Printf("MillisecondTimerClass low = %d, high = %d\n");

        Frequency = LI_TO_DBL(dh, dl) / 1000;
    }
}
