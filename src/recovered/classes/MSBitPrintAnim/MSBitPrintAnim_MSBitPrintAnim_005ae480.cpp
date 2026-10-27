// MSBitPrintAnim::MSBitPrintAnim(WideString const &text, Rect const &rect, bool unknown_31) (0x005AE480)
// Unicode text shown in a screen rectangle; positioned at the rectangle's corner.
#include "shared/ms_anim.hpp"
// @ref ??_7MSBitPrintAnim@@6B@=007a6e2c
// @ref ??_7MSAnim@@6B@=007a6d3c
// @ref ??0WideString@@QAE@ABV0@@Z=0076fa10
// Slots 4 and 5 are near misses, not in this unit's plan yet:
// @ref ?Unknown_Slot4@MSBitPrintAnim@@UAE_NPAVSurface@@PAVRect@@@Z=005ae560
// @ref ?Draw@MSBitPrintAnim@@UAEXPAVSurface@@PBVRect@@@Z=005ae620
// @ref ??_EMSBitPrintAnim@@UAEPAXI@Z=005afe50

MSBitPrintAnim::MSBitPrintAnim(WideString const &text, Rect const &rect, bool unknown_31) :
    MSAnim(rect.X, rect.Y),
    Text(text),
    TextRect(rect),
    unknown_30(false),
    unknown_31(unknown_31)
{
}
