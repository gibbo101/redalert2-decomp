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
#ifdef RA2_CDTIMER_NAMED_DURATION
    CDTimerClass(long set) {
        long started = Timer;
        long duration = set;
        Started = started;
        DelayTime = duration;
    }
#else
    CDTimerClass(long set) : Started(Timer), DelayTime(set) {}
#endif
    CDTimerClass(NoInitClass const &noinit) {}
    // Empty but user-declared (TS's TTimerClass has ~TTimerClass() {}): the
    // static timers of Scroll.cpp (0x00AB7048) and Mouse.cpp (0x00A70F70)
    // register atexit destructors that only set their guard bits.
    ~CDTimerClass() {}

    // The time left (Westwood's operator long); UnknownStage::Graphic_Logic
    // tests `Timer == 0` through it (TerrainClass::AI 0x006E3F10).
    operator long() const { return Value(); }
    // Value tests Started against 0xFFFFFFFFU as Westwood's FTIMER.H does (an
    // unsigned test): VC6 then keeps it after Stop's signed test, as
    // TActionClass 0x006B0A60 does (stop the mission timer).
#ifdef RA2_CDTIMER_VALUE_SOURCE
    long Value() const;
#else
    long Value() const
    {
        long remain = DelayTime;
        if (Started != 0xFFFFFFFFU) {
            long value = Timer - Started;
            if (value < remain) {
                return remain - value;
            } else {
                return 0;
            }
        }
        return remain;
    }
#endif
    bool Is_Active() const { return Started != -1; }
#ifdef RA2_CDTIMER_STOP_SOURCE
    // The owning unit supplies the original out-of-line specialization.
    void Stop();
#else
    void Stop()
    {
        if (Started != -1) {
            DelayTime = Value();
            Started = -1;
        }
    }
#endif
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

// A frame timer that TechnoClass 0x006D7990 restarts at 25 and Scenario.cpp's
// post-load refresh 0x0065D2C0 restarts from the current frame (0x00AC0178;
// declared here so units without the TechnoClass layout can use it).
extern CDTimerClass<FrameTimerClass> unknown_timer_ac0178;  // 0x00AC0178

#endif
