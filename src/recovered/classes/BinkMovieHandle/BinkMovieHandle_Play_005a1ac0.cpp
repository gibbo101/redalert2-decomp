// void BinkMovieHandle::Play() (0x005A1AC0)
// Plays the Bink movie as the current handle.
// @ref ?Unknown_00430430@BinkClass@@QAEXXZ=00430430
#include "shared/movie.hpp"

void BinkMovieHandle::Play()
{
    CurrentMovieHandle = this;
    Bink->Unknown_00430430();
    CurrentMovieHandle = 0;
}
