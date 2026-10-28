// void ScoreAnimClass::Pause() -- 0x00668300 (slot 1)
// Purpose: stops the score animation's system-clock countdown at +0x0C: a
// running timer keeps the time left in DelayTime and goes back to -1.
// Assumptions: CDTimerClass<SystemTimerClass>::Stop with Value() expanded in
// place; only this spelling reproduces the cached Started load.
#include "shared/score_anim.hpp"
// @ref ??BSystemTimerClass@@QBEJXZ=0069a430

void ScoreAnimClass::Pause()
{
    if (Timer.Started != -1) {
        Timer.DelayTime = Timer.Value();
        Timer.Started = -1;
    }
}
