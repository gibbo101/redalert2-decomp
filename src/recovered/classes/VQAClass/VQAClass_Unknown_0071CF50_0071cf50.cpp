// void VQAClass::Unknown_0071CF50(int frame) (0x0071CF50): seeks to the frame (-1: the last one) and plays it.
#include "shared/movie.hpp"

void VQAClass::Unknown_0071CF50(int frame)
{
    if (frame == -1) {
        frame = FrameCount - 1;
    }
    if (CurrentFrame != frame) {
        Unknown_0071CC60(frame);
        CurrentFrame = frame;
    }
    Unknown_0071CCD0(frame, 0);
    if ((unsigned)CurrentFrame >= (unsigned)FrameCount) {
        CurrentFrame = 0;
    }
}
