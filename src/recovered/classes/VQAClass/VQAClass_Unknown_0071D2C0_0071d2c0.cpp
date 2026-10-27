// void VQAClass::Unknown_0071D2C0(int unknown1, unsigned unknown2) (0x0071D2C0)
#include "shared/movie.hpp"
// @ref ?VQA_Unknown_0070B7F0@@YIXHI@Z=0070b7f0

void VQAClass::Unknown_0071D2C0(int unknown1, unsigned unknown2)
{
    if (unknown_508 != -1) {
        VQA_Unknown_0070B7F0(unknown1, unknown2 / 2);
    }
    unknown_544 = CurrentFrame;
}
