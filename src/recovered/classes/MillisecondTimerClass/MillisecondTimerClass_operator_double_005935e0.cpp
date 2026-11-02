#include "shared/milsectmr.hpp"

MillisecondTimerClass::operator double() const
{
    static int cpu_type = -1;
    static bool has_mmx = false;

    if (cpu_type == -1) {
        Get_CPU_Info(&cpu_type, (unsigned char *)&has_mmx, 0, 0);
    }
    if (Frequency != 1.0 && cpu_type > 4) {
        unsigned long high;
        unsigned long low;

        low = Get_CPU_Clock(high);
        double dl = low;
        double dh = high;

        return LI_TO_DBL(dh, dl) / Frequency;
    }

    return timeGetTime();
}
