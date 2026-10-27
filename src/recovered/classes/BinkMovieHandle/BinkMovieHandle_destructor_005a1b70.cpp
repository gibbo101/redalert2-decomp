// BinkMovieHandle::~BinkMovieHandle() (0x005A1B70)
// Deletes the Bink wrapper.
// @ref ??1BinkClass@@QAE@XZ=0042fee0
#include "shared/movie.hpp"

BinkMovieHandle::~BinkMovieHandle()
{
    delete Bink;
}
