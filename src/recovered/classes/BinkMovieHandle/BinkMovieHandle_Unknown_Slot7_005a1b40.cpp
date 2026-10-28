// void BinkMovieHandle::Unknown_Slot7(int frame) (0x005A1B40)
// Forwards the seek to the Bink wrapper.
// @ref ?Unknown_004303A0@BinkClass@@QAEXH@Z=004303a0
#include "shared/movie.hpp"

void BinkMovieHandle::Unknown_Slot7(int frame)
{
    Bink->Unknown_004303A0(frame);
}
