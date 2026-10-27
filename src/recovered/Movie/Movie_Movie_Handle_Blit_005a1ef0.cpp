// void __fastcall Movie_Handle_Blit() (0x005A1EF0)
// Draws the frame of the playing movie handle, if any.
#include "shared/movie.hpp"

void __fastcall Movie_Handle_Blit()
{
    if (CurrentMovieHandle) {
        CurrentMovieHandle->Blit();
    }
}
