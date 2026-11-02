// Benchmark::End (0x0042F140): adds the interval since Begin; once MAXIMUM_EVENT_COUNT (256) events are
// averaged, the oldest share decays instead of the count growing (Westwood's Bench.cpp).
#include "shared/bench.hpp"

void Benchmark::End()
{
    unsigned long value = Clock;
    if (Counter == 256) {
        Average -= Average / 256;
        Average += value;
    } else {
        Average += value;
        Counter++;
    }
    TotalCount++;
}
