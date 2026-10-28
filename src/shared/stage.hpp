// A frame-stepped stage (0x18 bytes: value, frame countdown, two counters;
// hypothesis: Westwood's StageClass). TechnoClass +0x1BC and the sidebar
// strips use it; TerrainClass +0x98 too (its Load keeps it through the
// NoInitClass constructor; Set_Rate restarts the countdown). SidebarClass keeps an out-of-line copy of the constructor (0x00682520).
#ifndef RA2_SHARED_STAGE_HPP
#define RA2_SHARED_STAGE_HPP

#include "shared/cd_timer.hpp"

class NoInitClass;

struct UnknownStage {
    UnknownStage() : Value(0), unknown_10(0), unknown_14(1) {}
    UnknownStage(NoInitClass const &noinit) : Timer(noinit) {}  // load path (TerrainClass)
    void Set_Rate(int rate)
    {
        Timer = rate;
        unknown_10 = rate;
    }
    int Fetch_Stage() const { return Value; }
    void Set_Stage(int stage) { Value = stage; }
    int Fetch_Rate() const { return unknown_10; }
    // Steps the stage when the timer has run out (hypothesis: Westwood's
    // StageClass::Graphic_Logic); true when it stepped.
    bool Graphic_Logic()
    {
        if (Timer == 0 && unknown_10 != 0) {
            Value += unknown_14;
            Timer = unknown_10;
            return true;
        }
        return false;
    }
    int Value;                                          // +0x00
    CDTimerClass<FrameTimerClass> Timer;                // +0x04
    int unknown_10;                                     // +0x10
    int unknown_14;                                     // +0x14 (step; 1)
};

#endif
