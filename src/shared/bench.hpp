// The CPU-clock benchmark (unit 0x0042F0A0-0x0042F1F7, Westwood's Bench.cpp as in the Red Alert and
// Tiberian Sun sources): a running total of clock/16 intervals. RA2 keeps its constructor, Reset,
// Begin, End (0x0042F140, unreferenced), Step and Value.
#ifndef RA2_SHARED_BENCH_HPP
#define RA2_SHARED_BENCH_HPP

// The Pentium time-stamp counter: the low half, the high half through high (0x0077F274).
unsigned long __cdecl Get_CPU_Clock(unsigned long &high);

// The time-stamp counter divided by 16.
class PentiumTimerClass {
public:
    unsigned long operator()() const
    {
        unsigned long high;
        unsigned long low = Get_CPU_Clock(high);
        return (low >> 4) | (high << 28);
    }
    operator unsigned long() const
    {
        unsigned long high;
        unsigned long low = Get_CPU_Clock(high);
        return (low >> 4) | (high << 28);
    }
};

// A timer counting T's ticks since it was set (Westwood's BasicTimerClass; RA2 keeps Started first;
// int Started and an int setting as in Westwood's TIMER.H).
template<class T>
class BasicTimerClass {
public:
    BasicTimerClass(int set = 0) : Started(Timer() - set) {}
    unsigned long Value() const { return Timer() - Started; }
    operator unsigned long() const { return Timer() - Started; }

protected:
    int Started;            // +0x00 (int as in Westwood TIMER.H; unsigned stores the Pentium value last)
    T Timer;                // +0x04
};

class Benchmark {
public:
    Benchmark();                                    // 0x0042F0C0
    void Begin(bool reset = false);                 // 0x0042F100
    void Reset();                                   // 0x0042F0F0
    void End();                                     // 0x0042F140 (adds the interval since Begin; a full average decays)
    unsigned long Value() const;                    // 0x0042F1E0 (the average interval)
    unsigned long Step();                           // 0x0042F1A0 (adds the interval since Begin; the event count)

private:
    BasicTimerClass<PentiumTimerClass> Clock;       // +0x00
    unsigned long Average;                          // +0x08 the accumulated time
    unsigned long Counter;                          // +0x0C
    unsigned long TotalCount;                       // +0x10
};

#endif
