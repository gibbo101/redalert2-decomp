// void BinkClass::Unknown_004303E0(int unknown) (0x004303E0): forwards to the companion.
#include "shared/movie.hpp"
// @ref ?Unknown_0069B4F0@VQAMovieCompanion@@QAEXH@Z=0069b4f0

void BinkClass::Unknown_004303E0(int unknown)
{
    if (Companion != 0) {
        Companion->Unknown_0069B4F0(unknown);
    }
}
