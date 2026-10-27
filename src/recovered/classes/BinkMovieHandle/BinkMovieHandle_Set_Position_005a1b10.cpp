// void BinkMovieHandle::Set_Position(int x, int y) (0x005A1B10)
// Forwards to the Bink wrapper.
// @ref ?Unknown_00430280@BinkClass@@QAEXHH@Z=00430280
#include "shared/movie.hpp"

void BinkMovieHandle::Set_Position(int x, int y)
{
    Bink->Unknown_00430280(x, y);
}
