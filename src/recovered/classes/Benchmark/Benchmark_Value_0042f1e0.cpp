// Benchmark::Value (0x0042F1E0): the average interval, 0 without events.
#include "shared/bench.hpp"

unsigned long Benchmark::Value() const
{
    if (Counter) {
        return Average / Counter;
    }
    return 0;
}
