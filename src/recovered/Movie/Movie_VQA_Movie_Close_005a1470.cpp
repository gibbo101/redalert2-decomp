// void __fastcall VQA_Movie_Close(VQAMovie *movie) (0x005A1470)
// Stops and frees the player and the companion object; clears Playing.
// @ref ??1VQAClass@@QAE@XZ=0071c8a0
// @ref ?Unknown_0071D1F0@VQAClass@@QAEXXZ=0071d1f0
// @ref ??1VQAMovieCompanion@@QAE@XZ=0069b2a0
#include "shared/movie.hpp"

void __fastcall VQA_Movie_Close(VQAMovie *movie)
{
    if (movie) {
        if (movie->Player) {
            movie->Player->Unknown_0071D1F0();
            delete movie->Player;
            movie->Player = 0;
        }
        if (movie->Companion) {
            delete movie->Companion;
            movie->Companion = 0;
        }
        movie->Playing = false;
    }
}
