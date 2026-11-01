// void __fastcall Play_Movie(int movie, int theme, bool clrscrn_after, bool stretch, bool clrscrn_before) (0x005A07F0)
// Plays the named movie of a movie-list index without a theme and with unknown_flag_a40380 cleared.
#include "shared/play_movie.hpp"
#include "shared/movie_list.hpp"
#include "shared/gscreen.hpp"
// @ref ?unknown_names_a71050@@3V?$DynamicVectorClass@PBD@@A=00a71050
// @ref ?unknown_flag_a40380@@3_NA=00a40380

void __fastcall Play_Movie(int movie, int theme, bool clrscrn_after, bool stretch, bool clrscrn_before)
{
    if (movie >= 0 && movie < unknown_names_a71050.Count()) {
        bool old = unknown_flag_a40380;
        unknown_flag_a40380 = false;
        Play_Movie(unknown_names_a71050[movie], -1, clrscrn_after, stretch, clrscrn_before, false);
        unknown_flag_a40380 = old;
    }
}
