// void VQAClass::Unknown_0071CC60(int frame) (0x0071CC60): seeks to the frame
// unless it is already current; the frame is kept when the seek (0x0077C2E0)
// does not fail with -6.
#include "shared/movie.hpp"
// @ref ?VQA_Unknown_0077C2E0@@YIHPAUVQAHandle@@HH@Z=0077c2e0

void VQAClass::Unknown_0071CC60(int frame)
{
    if (frame != CurrentFrame) {
        if (VQA_Unknown_0077C2E0(Handle, frame, 0) != -6) {
            CurrentFrame = frame;
        }
    }
}
