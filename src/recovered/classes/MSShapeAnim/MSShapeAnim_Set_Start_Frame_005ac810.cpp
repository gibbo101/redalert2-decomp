// void MSShapeAnim::Set_Start_Frame(int frame) (0x005AC810)
#include "shared/ms_anim.hpp"

void MSShapeAnim::Set_Start_Frame(int frame)
{
    StartFrame = frame;
    if (StartFrame >= (unsigned)Shape->FrameCount) {
        StartFrame = Shape->FrameCount - 1;
    }
}
