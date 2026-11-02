// MillisecondTimerClass (Westwood's milsectmr.cpp as in the Tiberian Sun sources, unit
// 0x00593530-0x00593674): a millisecond clock read from the time-stamp counter scaled by the
// performance counter frequency, or from the multimedia timer (raised to 1 ms resolution while
// the timer lives) when no frequency is reported. Frequency stays 1.0 in the second case.
#ifndef RA2_SHARED_MILSECTMR_HPP
#define RA2_SHARED_MILSECTMR_HPP

class MillisecondTimerClass {
public:
    MillisecondTimerClass();                // 0x00593530
    ~MillisecondTimerClass();               // 0x005935C0
    operator double() const;                // 0x005935E0 (milliseconds)

    double Frequency;                       // +0x00 counter ticks per millisecond, 1.0 without one
};

// The game's millisecond timer (0x00837448; defined in the unit at 0x0040CE70).
extern MillisecondTimerClass MillisecondTimer;

#endif
