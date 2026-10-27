// VQAMovie::~VQAMovie() (0x005A1760)
// Stops and frees the player and the companion object.
#include "shared/movie.hpp"

VQAMovie::~VQAMovie()
{
    if (Player) {
        Player->Unknown_0071D1F0();
        delete Player;
    }
    if (Companion) {
        delete Companion;
        Companion = 0;
    }
}
