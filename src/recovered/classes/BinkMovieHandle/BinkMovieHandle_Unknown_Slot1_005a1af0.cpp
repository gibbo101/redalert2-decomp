// bool BinkMovieHandle::Unknown_Slot1() (0x005A1AF0)
// Forwards to the Bink wrapper.
// @ref ?Unknown_00430800@BinkClass@@QAE_NXZ=00430800
#include "shared/movie.hpp"

bool BinkMovieHandle::Unknown_Slot1()
{
    return Bink->Unknown_00430800();
}
