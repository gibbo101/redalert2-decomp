// Westwood's countdown timer and its time sources (moved out of
// shared/ms_anim.hpp, which keeps SystemTimerClass): Started is -1 while
// stopped; FrameTimerClass counts game frames (0x00A40D2C).
#ifndef RA2_SHARED_CD_TIMER_HPP
#define RA2_SHARED_CD_TIMER_HPP

class NoInitClass;

extern int Frame;                       // 0x00A40D2C game frame counter

class FrameTimerClass {
public:
    operator long() const { return Frame; }
};

template <class T>
class CDTimerClass {
public:
    CDTimerClass() : Started(Timer), DelayTime(0) {}
    CDTimerClass(long set) : Started(Timer), DelayTime(set) {}
    CDTimerClass(NoInitClass const &noinit) {}
    // Empty but user-declared (TS's TTimerClass has ~TTimerClass() {}): the
    // static timers of Scroll.cpp (0x00AB7048) and Mouse.cpp (0x00A70F70)
    // register atexit destructors that only set their guard bits.
    ~CDTimerClass() {}

    long Value() const
    {
        long remain = DelayTime;
        if (Started != -1) {
            long value = Timer - Started;
            if (value < remain) {
                return remain - value;
            } else {
                return 0;
            }
        }
        return remain;
    }
    void Stop()
    {
        if (Started != -1) {
            DelayTime = Value();
            Started = -1;
        }
    }
    void Start()
    {
        if (Started == -1) {
            Started = Timer;
        }
    }

    long Started;           // +0x00
    T Timer;                // +0x04
    long DelayTime;         // +0x08
};

#endif
