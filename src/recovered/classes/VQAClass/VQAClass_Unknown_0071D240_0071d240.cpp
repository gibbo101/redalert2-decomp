// bool VQAClass::Unknown_0071D240(int unknown1, int x, int y, int width, int height) (0x0071D240)
// -1 keeps the saved position and gives a zero size.
#include "shared/movie.hpp"
// @ref ?VQA_Unknown_0077C480@@YIHPAUVQAHandle@@HHHHH@Z=0077c480

bool VQAClass::Unknown_0071D240(int unknown1, int x, int y, int width, int height)
{
    if (x == -1) {
        x = unknown_518;
    } else {
        unknown_518 = x;
    }
    if (y == -1) {
        y = unknown_51c;
    } else {
        unknown_51c = y;
    }
    if (width == -1) {
        width = 0;
    }
    if (height == -1) {
        height = 0;
    }
    return VQA_Unknown_0077C480(Handle, unknown1, x, y, width, height) == -1 ? true : false;
}
