// void __fastcall Pause_Ingame_Movie(bool pause) (0x005A0A90)
// Pauses or resumes the first queued movie.
#include "shared/play_movie.hpp"
#include "shared/movie.hpp"
#include "shared/movie_queue.hpp"
#include "shared/audio_pause.hpp"

void __fastcall Pause_Ingame_Movie(bool pause)
{
    if (Unknown_Movies_Queued_005a0ab0()) {
        queued_movies_00af8fd8[0]->Pause(pause);
    }
}
// @ref ?queued_movies_00af8fd8@@3V?$DynamicVectorClass@PAVMovieHandle@@@@A=00af8fd8
