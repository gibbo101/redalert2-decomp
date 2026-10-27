// void VQMovieHandle::Play() (0x005A1830)
// Plays the whole movie as the current handle.
// @ref ?CurrentMovieHandle@@3PAVMovieHandle@@A=00a710b0
// @ref ?VQA_Movie_Play@@YIXPAVVQAMovie@@_NHH@Z=005a14d0
#include "shared/movie.hpp"

MovieHandle *CurrentMovieHandle;   // 0x00A710B0: the handle playing now

void VQMovieHandle::Play()
{
    CurrentMovieHandle = this;
    VQA_Movie_Play(Movie, true, -1, 0);
    CurrentMovieHandle = 0;
}
