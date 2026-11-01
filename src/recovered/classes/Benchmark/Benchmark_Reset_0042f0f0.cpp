// Benchmark::Reset (0x0042F0F0): forgets the events.
#include "shared/bench.hpp"

void Benchmark::Reset()
{
    Average = 0;
    Counter = 0;
    TotalCount = 0;
}
