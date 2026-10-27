// bool VQAClass::Unknown_0071CBE0(int unknown1, int unknown2) (0x0071CBE0)
#include "shared/movie.hpp"
// @ref ?VQA_Unknown_0077C640@@YIHPAUVQAHandle@@HHH@Z=0077c640

bool VQAClass::Unknown_0071CBE0(int unknown1, int unknown2)
{
    if (unknown2 < 0) {
        unknown2 = -1;
    }
    return VQA_Unknown_0077C640(Handle, unknown1, unknown2, 1) == -1 ? true : false;
}
