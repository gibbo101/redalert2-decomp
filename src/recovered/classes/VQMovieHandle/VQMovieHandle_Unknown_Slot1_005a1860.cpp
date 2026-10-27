// bool VQMovieHandle::Unknown_Slot1() (0x005A1860)
// Steps the movie while it is playing; the player reports Finished.
#include "shared/movie.hpp"

bool VQMovieHandle::Unknown_Slot1()
{
    if (!Movie->Player->unknown_548 && Movie->Playing) {
        return VQA_Movie_Unknown_005A15F0(Movie, &Finished);
    }
    return false;
}
