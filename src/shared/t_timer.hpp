// TTimerClass: Westwood's count-up timer (moved out of shared/comm_buffer.hpp
// so a class header can hold one as a member). T is the time source
// (shared/system_timer.hpp's SystemTimerClass, shared/cd_timer.hpp's
// FrameTimerClass).
#ifndef RA2_SHARED_T_TIMER_HPP
#define RA2_SHARED_T_TIMER_HPP

// A count-up timer (hypothesis: Westwood's TTimerClass): the accumulated
// time plus the running time since Started (-1 while stopped).
template <class T>
class TTimerClass {
public:
    TTimerClass(long set = 0) : Started(Timer), Accumulated(set) {}
    long Time() const
    {
        long value = Accumulated;
        if (Started != -1) {
            value += Timer - Started;
        }
        return value;
    }
    void Stop()
    {
        if (Started != -1) {
            Accumulated += Timer - Started;
            Started = -1;
        }
    }
    long Started;           // +0x00
    T Timer;                // +0x04
    long Accumulated;       // +0x08
};

#endif
