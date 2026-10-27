// void VQAClass::Unknown_0071D1A0() (0x0071D1A0): pause.
#include "shared/movie.hpp"
// @ref ?VQA_Unknown_0077BF10@@YIHPAUVQAHandle@@HH@Z=0077bf10

void VQAClass::Unknown_0071D1A0()
{
    if (Opened && !unknown_548) {
        VQA_Unknown_0077BF10(Handle, 2, 0);
    }
    unknown_548 = true;
}
