// int __fastcall Is_Movie_Active() (0x005A1ED0)
// Whether a VQA movie or a movie handle is playing.
#include "shared/movie.hpp"

int __fastcall Is_Movie_Active()
{
    if (CurrentVQAMovie || CurrentMovieHandle) {
        return 1;
    }
    return 0;
}
