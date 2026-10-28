// void __fastcall Unknown_Queue_Movie_005a0840(char const *name, bool flag) (0x005A0840)
// Outside a game, opens the movie on the sidebar surface, puts it at the radar's corner, sets its end callback
// (0x005A08F0) and flag, and adds it to the queued movies.
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ADD
#include "shared/movie_queue.hpp"
#include "shared/movie.hpp"
// @ref ?queued_movies_00af8fd8@@3V?$DynamicVectorClass@PAVMovieHandle@@@@A=00af8fd8
// @ref ?unknown_radar_x_8336cc@@3HA=008336cc
// @ref ?unknown_radar_y_8336d0@@3HA=008336d0
// @ref ?unknown_surface_839948@@3PAVSurface@@A=00839948
// @ref ?unknown_game_mode_a3d298@@3HA=00a3d298
// @ref ?Create_Movie_Handle@@YIPAVMovieHandle@@PBDPAVSurface@@PBVRect@@@Z=005a1d30
// @ref ?Unknown_Movie_Message_005a08f0@@YIXH@Z=005a08f0

void __fastcall Unknown_Queue_Movie_005a0840(char const *name, bool flag)
{
    if (unknown_game_mode_a3d298 == 0) {
        MovieHandle *movie = Create_Movie_Handle(name, unknown_surface_839948, 0);
        if (movie != 0) {
            movie->Set_Position(unknown_radar_x_8336cc - 3, unknown_radar_y_8336d0 - 1);
            movie->Unknown_Slot8((int)Unknown_Movie_Message_005a08f0);
            movie->unknown_04 = flag;
            queued_movies_00af8fd8.Add(movie);
        }
    }
}
