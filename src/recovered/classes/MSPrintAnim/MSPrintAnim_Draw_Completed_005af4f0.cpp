// @ref ?Get_Char@WideString@@QBEGI@Z=00770470
// @ref ?Intersect@@YI?AVRect@@ABV1@0PAH1@Z=0041fdf0
#include "shared/ms_anim.hpp"
void MSPrintAnim::Draw_Completed_005af4f0(Surface *surface, Rect const *clip)
{
    if (clip != 0) {
        Rect area=clip->Intersect(TextRect);
        if (!area.Is_Valid()) return;
    }
    int x=X;
    int y=Y;
    unsigned end=LineStart;
    for (unsigned index=0;index<end;++index) {
        if (Text.Get_Char(index)=='\n') {
            x=X;
            int height=Font->Get_Font_Height();
            y+=height;
            if (y+height>=surface->Get_Height()) return;
        } else {
            Font->Print_Char(surface,Text.Get_Char(index),x,y,2,1);
            x+=Font->Char_Width(Text.Get_Char(index));
        }
    }
}
