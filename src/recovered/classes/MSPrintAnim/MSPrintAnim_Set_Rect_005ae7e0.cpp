// @ref ??0Rect@@QAE@HHHH@Z=0042bcd0
// @ref ?Get@WideString@@QBEPBGXZ=007703f0
// @ref ?Text_Rect@MSFont@@QAEXPBGAAVRect@@@Z=005b41f0
#include "shared/ms_anim.hpp"
void MSPrintAnim::Set_Rect(Rect const &rect)
{
    if (rect.Is_Valid()) {
        Measure_Text();
        X += (rect.Width - TextRect.Width) / 2;
        int line_height=Font->Height;
        Y += (rect.Height - (rect.Height / line_height) * line_height) / 2;
        TextRect.X += X;
        TextRect.Y += Y;
        TextRect = rect.Intersect(TextRect);
        X += Font->Width / 2;
    } else {
        Measure_Text();
        TextRect.X = X;
        TextRect.Y = Y;
    }
}
