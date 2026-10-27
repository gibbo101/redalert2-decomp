// void VQAClass::Unknown_0071D210() (0x0071D210)
#include "shared/movie.hpp"
// @ref ?VQA_Unknown_0077C7D0@@YIXPAUVQAHandle@@@Z=0077c7d0
// @ref ?Unknown_0069B4E0@VQAMovieCompanion@@QAEXXZ=0069b4e0

void VQAClass::Unknown_0071D210()
{
    VQA_Unknown_0077C7D0(Handle);
    if (Companion != 0) {
        Companion->Unknown_0069B4E0();
    }
}
