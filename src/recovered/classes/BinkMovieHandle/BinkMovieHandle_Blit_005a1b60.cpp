// void BinkMovieHandle::Blit() (0x005A1B60)
// Forwards to the Bink wrapper.
// @ref ?Unknown_00430820@BinkClass@@QAEXXZ=00430820
#include "shared/movie.hpp"

void BinkMovieHandle::Blit()
{
    Bink->Unknown_00430820();
}
