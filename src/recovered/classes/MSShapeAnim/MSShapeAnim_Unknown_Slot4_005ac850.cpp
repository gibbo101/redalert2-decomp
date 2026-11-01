// @ref ??0Rect@@QAE@HHHH@Z=0042bcd0
// @ref ??BSystemTimerClass@@QBEJXZ=0069a430
// @ref ?CC_Draw_Shape@@YIXPAVSurface@@PAVConvertClass@@PBUShapeFileStruct@@HABUPoint2D@@ABVRect@@HHHHHHHU4@@Z=0049eea0
// @ref ?unknown_surface_839958@@3PAVSurface@@A=00839958
#include "shared/ms_anim.hpp"
bool MSShapeAnim::Unknown_Slot4(Surface *surface, Rect *dirty)
{
    if (unknown_0C == true && Timer.Value()==0) {
        Timer=unknown_24;
        Rect old=Frame_Rect();
        old.X=X+old.X; old.Y=old.Y+Y;
        if (Flags & 0x200) { old.X-=Shape->Width/2; old.Y-=Shape->Height/2; }
        surface->Copy_From(old,*unknown_surface_839958,old,false,true);
        if (++Frame>EndFrame) {
            if (!unknown_34) { *dirty=old; return true; }
            Frame=StartFrame;
        }
        CC_Draw_Shape(surface,Drawer,Shape,Frame,Point2D(X,Y),surface->Get_Rect(),Flags|0x400,0,0,0,1000,0,0,Point2D(0,0));
        *dirty=Frame_Rect(); dirty->X=dirty->X+X; dirty->Y=dirty->Y+Y;
        if (Flags & 0x200) { dirty->X-=Shape->Width/2; dirty->Y-=Shape->Height/2; }
        *dirty=Union(*dirty,old);
        return false;
    }
    dirty->Set(0,0,0,0);
    return false;
}
