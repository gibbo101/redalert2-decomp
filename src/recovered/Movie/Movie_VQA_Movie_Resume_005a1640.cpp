// void __fastcall VQA_Movie_Resume(VQAMovie *movie) (0x005A1640)
// Resumes the movie's player, if any.
// @ref ?Unknown_0071D1E0@VQAClass@@QAEXXZ=0071d1e0
#include "shared/movie.hpp"

void __fastcall VQA_Movie_Resume(VQAMovie *movie)
{
    if (movie && movie->Player) {
        movie->Player->Unknown_0071D1E0();
    }
}
