// ScoreAnimClass::ScoreAnimClass(int x, int y, void const *data) (0x006682C0)
#include "shared/score_anim.hpp"
// @ref ??_7ScoreAnimClass@@6B@=007a928c
// @ref ??BSystemTimerClass@@QBEJXZ=0069a430
// @ref __purecall=004b8960

ScoreAnimClass::ScoreAnimClass(int x, int y, void const *data) :
    XPos(x),
    YPos(y),
    Timer(0),
    DataPtr(data)
{
}
