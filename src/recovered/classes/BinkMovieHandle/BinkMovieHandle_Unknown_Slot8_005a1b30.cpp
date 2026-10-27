// void BinkMovieHandle::Unknown_Slot8(int unknown) (0x005A1B30)
// Forwards to the Bink wrapper.
// @ref ?Unknown_004303E0@BinkClass@@QAEXH@Z=004303e0
#include "shared/movie.hpp"

void BinkMovieHandle::Unknown_Slot8(int unknown)
{
    Bink->Unknown_004303E0(unknown);
}
