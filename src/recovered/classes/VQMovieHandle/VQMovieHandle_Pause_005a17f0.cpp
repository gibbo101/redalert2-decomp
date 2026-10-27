// void VQMovieHandle::Pause(bool pause) (0x005A17F0)
// Pauses or resumes the movie.
#include "shared/movie.hpp"

void VQMovieHandle::Pause(bool pause)
{
    if (pause) {
        VQA_Movie_Pause(Movie);
    } else {
        VQA_Movie_Resume(Movie);
    }
}
