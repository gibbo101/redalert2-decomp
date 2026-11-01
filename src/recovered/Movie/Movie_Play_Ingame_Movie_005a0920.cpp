// void __fastcall Play_Ingame_Movie(int movie, bool flag) (0x005A0920)
// Queues the movie of a movie-list index for the radar.
#include "shared/play_movie.hpp"
#include "shared/movie_list.hpp"
#include "shared/movie_queue.hpp"

void __fastcall Play_Ingame_Movie(int movie, bool flag)
{
    if (movie >= 0 && movie < unknown_names_a71050.Count()) {
        Unknown_Queue_Movie_005a0840(unknown_names_a71050[movie], flag);
    }
}
// @ref ?Create_Movie_Handle@@YIPAVMovieHandle@@PBDPAVSurface@@PBVRect@@@Z=005a1d30
// @ref ?queued_movies_00af8fd8@@3V?$DynamicVectorClass@PAVMovieHandle@@@@A=00af8fd8
// @ref ?unknown_game_mode_a3d298@@3HA=00a3d298
// @ref ?unknown_names_a71050@@3V?$DynamicVectorClass@PBD@@A=00a71050
// @ref ?unknown_radar_x_8336cc@@3HA=008336cc
// @ref ?unknown_radar_y_8336d0@@3HA=008336d0
// @ref ?unknown_surface_839948@@3PAVSurface@@A=00839948
