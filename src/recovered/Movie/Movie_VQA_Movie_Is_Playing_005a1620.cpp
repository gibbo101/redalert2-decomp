// bool __fastcall VQA_Movie_Is_Playing() (0x005A1620)
// Whether a VQA movie is playing.
#include "shared/movie.hpp"

bool __fastcall VQA_Movie_Is_Playing()
{
    return CurrentVQAMovie != 0;
}
