#include "shared/score_anim.hpp"
// @ref ??_7ScoreTimeClass@@6B@=007a9278
// @ref ??BSystemTimerClass@@QBEJXZ=0069a430
ScoreTimeClass::ScoreTimeClass(int x, int y, void const *data, int maxStage, int delay, ConvertClass *drawer) :
    ScoreAnimClass(x,y,data),
    Stage(0),
    MaxStage(maxStage),
    DelayFrames(delay),
    Drawer(drawer)
{
}

// External references checked against complete original body operands.
// @ref ??BSystemTimerClass@@QBEJXZ=0069a430
// @ref ??_7ScoreTimeClass@@6B@=007a9278
