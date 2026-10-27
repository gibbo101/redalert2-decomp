// void MSShapeAnim::Set_End_Frame(int frame) (0x005AC830)
#include "shared/ms_anim.hpp"

void MSShapeAnim::Set_End_Frame(int frame)
{
    EndFrame = frame;
    if (EndFrame >= (unsigned)Shape->FrameCount) {
        EndFrame = Shape->FrameCount - 1;
    }
}
