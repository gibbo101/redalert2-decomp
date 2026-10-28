// void ScoreAnimClass::Resume() -- 0x00668350 (slot 2)
// Purpose: starts the score animation's system-clock countdown at +0x0C: an
// unstarted timer (Started == -1) takes the current time (SystemTimerClass,
// 0x0069A430).
#include "shared/score_anim.hpp"
// @ref ??BSystemTimerClass@@QBEJXZ=0069a430

void ScoreAnimClass::Resume()
{
    Timer.Start();
}
