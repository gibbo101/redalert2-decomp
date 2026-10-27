// bool VQAClass::Unknown_0071CC10(int unknown1, int unknown2, int unknown3) (0x0071CC10)
// Frame range (clamped to the movie) and count.
#include "shared/movie.hpp"
// @ref ?VQA_Unknown_0077C6C0@@YIHPAUVQAHandle@@HHHH@Z=0077c6c0

bool VQAClass::Unknown_0071CC10(int unknown1, int unknown2, int unknown3)
{
    if (unknown1 < 0 || unknown1 >= FrameCount) {
        unknown1 = 0;
    }
    if (unknown2 < 0 || unknown2 >= FrameCount) {
        unknown2 = FrameCount - 1;
    }
    if (unknown3 < 0) {
        unknown3 = -1;
    }
    return VQA_Unknown_0077C6C0(Handle, unknown1, unknown2, unknown3, 0) == -1 ? true : false;
}
