// VQMovieHandle::~VQMovieHandle() (0x005A1A00)
// Closes the movie (the wrapper itself is not freed).
#include "shared/movie.hpp"

VQMovieHandle::~VQMovieHandle()
{
    VQA_Movie_Close(Movie);
}
