// void VQAClass::Unknown_0071D1F0() (0x0071D1F0): stop.
#include "shared/movie.hpp"
// @ref ?VQA_Unknown_0077BE70@@YIXPAUVQAHandle@@@Z=0077be70

void VQAClass::Unknown_0071D1F0()
{
    if (Opened) {
        VQA_Unknown_0077BE70(Handle);
    }
}
