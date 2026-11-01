// Benchmark::Step (0x0042F1A0): adds the interval since Begin as one event; the event count.
#include "shared/bench.hpp"

unsigned long Benchmark::Step()
{
    unsigned long value = Clock;
    Average += value;
    Counter++;
    TotalCount++;
    return TotalCount;
}
