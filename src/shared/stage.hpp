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

// Westwood's animation stage counter (AnimClass +0x98, LaserDrawClass +0x00),
// moved here from shared/anim.hpp. Same layout as UnknownStage, with other
// inline helpers.
// StageClass's frame countdown. Its NoInitClass constructor is called out of
// line (0x00423F60, an empty COMDAT shared with TeamClass's
// UnknownTimer423F60 in shared/techno.hpp); hypothesis for the original
// class shape.
class StageTimerClass : public CDTimerClass<FrameTimerClass> {
public:
    StageTimerClass(long set) : CDTimerClass<FrameTimerClass>(set) {}
    StageTimerClass(NoInitClass const &noinit);         // 0x00423F60
};

class StageClass {
public:
    StageClass() : Stage(0), StageTimer(0), Rate(0), Step(1) {}
    StageClass(NoInitClass const &noinit) : StageTimer(noinit) {}

#ifdef RA2_STAGE_SETTERS
    void Set_Stage(int frame) { Stage = frame; }
    void Set_Step(int increment) { Step = increment; }
    int Fetch_Step() const { return Step; }
#endif

#ifdef RA2_VEIN_STAGE_ACCESSORS
    int Fetch_Stage() const { return Stage; }
#endif
    void Set_Rate(int rate)
    {
        CDTimerClass<FrameTimerClass> reset(rate);
        static_cast<CDTimerClass<FrameTimerClass> &>(StageTimer) = reset;
        Rate = rate;
    }

    // Inline StageClass operations observed in FactoryClass::AI (0x004B9300); names are hypotheses.
    bool Ready_For_Advance() const { return StageTimer.Value()==0 && Rate!=0; }
    bool Advance_Stage_When_Ready()
    {
        if(!Ready_For_Advance()) return false;
        Stage=(int)((unsigned int)Stage+(unsigned int)Step);
        StageTimer=Rate;
        return true;
    }

    // Original stage advance operation, used through TechnoClass's actual StageClass base.
    bool Graphic_Logic()
    {
        if (Ready_For_Advance()) {
            Stage = (int)((unsigned int)Stage + (unsigned int)Step);
#ifdef RA2_VEIN_STAGE_GRAPHIC_ASSIGN
            StageTimer=Rate;
#else
            CDTimerClass<FrameTimerClass> reset(Rate);
            static_cast<CDTimerClass<FrameTimerClass> &>(StageTimer) = reset;
#endif
            return true;
        }
        return false;
    }

    int Stage;                                  // +0x00
    StageTimerClass StageTimer;                 // +0x04
    int Rate;                                   // +0x10
    int Step;                                   // +0x14 frame step (1; -1 for Reverse types)
};

#endif
