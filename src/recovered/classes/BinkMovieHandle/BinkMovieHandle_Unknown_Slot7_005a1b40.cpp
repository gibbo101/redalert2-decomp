// int BinkMovieHandle::Unknown_Slot7(int unknown) (0x005A1B40)
// Forwards to the Bink wrapper.
// @ref ?Unknown_004303A0@BinkClass@@QAEHH@Z=004303a0
#include "shared/movie.hpp"

int BinkMovieHandle::Unknown_Slot7(int unknown)
{
    return Bink->Unknown_004303A0(unknown);
}
