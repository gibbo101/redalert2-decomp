// ScorePrintClass::ScorePrintClass(void const *string, int x, int y, void const *palette, bool background) (0x006680A0)
#include "shared/score_anim.hpp"
// @ref ??_7ScoreAnimClass@@6B@=007a928c
// @ref ??BSystemTimerClass@@QBEJXZ=0069a430
// @ref __purecall=004b8960
// @ref ??_7ScorePrintClass@@6B@=007a9264

ScorePrintClass::ScorePrintClass(void const *string, int x, int y, void const *palette, bool background) :
    ScoreAnimClass(x, y, string),
    Stage(0),
    unknown_20(0),
    Background(background),
    PrimaryPalette(palette)
{
}
