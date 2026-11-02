// Benchmark::Begin (0x0042F100): restarts the clock, clearing the statistics first when asked (Westwood's
// Bench.cpp).
#include "shared/bench.hpp"

void Benchmark::Begin(bool reset)
{
    if (reset) Reset();
    Clock = 0;
}
