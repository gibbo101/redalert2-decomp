// bool BinkMovieHandle::Is_Finished() (0x005A1AE0)
// Forwards to the Bink wrapper.
// @ref ?Unknown_00430420@BinkClass@@QAE_NXZ=00430420
#include "shared/movie.hpp"

bool BinkMovieHandle::Is_Finished()
{
    return Bink->Unknown_00430420();
}
