// bool ScoreTimeClass::Update(int unknown) (0x00667F90, slot 3)
// Each time the timer runs out: restart it, advance the frame (wrapping at
// MaxStage) and draw it on both score surfaces (Westwood's SCORE.CPP).
// The unit's shape helpers fall back on Score.cpp's empty rectangle.
#define SHAPE_FILE_EMPTY_RECT unknown_score_empty_rect_ab6f20
#include "shared/score_font.hpp"
#include "shared/score_anim.hpp"
#include "shared/palette.hpp"
#include "shared/dsurface.hpp"
#include "shared/unknown_globals.hpp"
// @ref ??BSystemTimerClass@@QBEJXZ=0069a430
// @ref ?CC_Draw_Shape@@YIXPAVSurface@@PAVConvertClass@@PBUShapeFileStruct@@HABUPoint2D@@ABVRect@@HHHHHHHU4@@Z=0049eea0
// @ref ?unknown_surface_839954@@3PAVSurface@@A=00839954
// @ref ?unknown_surface_839958@@3PAVSurface@@A=00839958



bool ScoreTimeClass::Update(int unknown)
{
    if (!Timer) {
        Timer = DelayFrames;
        if (++Stage >= MaxStage) {
            Stage = 0;
        }
        CC_Draw_Shape(unknown_surface_839954, Drawer, (ShapeFileStruct const *)DataPtr, Stage,
                      Point2D(XPos, YPos), unknown_surface_839954->Get_Rect(), 0x400, 0, 0, 0, 1000, 0, 0, Point2D(0, 0));
        CC_Draw_Shape(unknown_surface_839958, Drawer, (ShapeFileStruct const *)DataPtr, Stage,
                      Point2D(XPos, YPos), unknown_surface_839958->Get_Rect(), 0x400, 0, 0, 0, 1000, 0, 0, Point2D(0, 0));
    }
    return false;
}
