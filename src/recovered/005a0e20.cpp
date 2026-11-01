// void Movie_Unlock_Surface() (0x005A0E20)
// The VQA player's unlock callback (TibSun Movie_Unlock_Surface): unlocks the current movie's frame surface.
#include "shared/movie.hpp"
// @ref ?CurrentVQAMovie@@3PAVVQAMovie@@A=00a710ac

void Movie_Unlock_Surface()
{
    CurrentVQAMovie->FrameSurface->Unlock();
}
