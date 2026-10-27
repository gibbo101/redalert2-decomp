// bool __fastcall VQA_Movie_Unknown_005A15F0(VQAMovie *movie, bool *unknown) (0x005A15F0)
// Runs one player step (0x0071CFC0) as the current movie unless another
// movie is playing.
// @ref ?Unknown_0071CFC0@VQAClass@@QAE_NPA_N@Z=0071cfc0
#include "shared/movie.hpp"

bool __fastcall VQA_Movie_Unknown_005A15F0(VQAMovie *movie, bool *unknown)
{
    if (CurrentVQAMovie) {
        return false;
    }
    CurrentVQAMovie = movie;
    bool result = movie->Player->Unknown_0071CFC0(unknown);
    CurrentVQAMovie = 0;
    return result;
}
