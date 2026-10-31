// bool Unknown_Movies_Queued_005a0ab0() (0x005A0AB0)
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#include "shared/movie_queue.hpp"
#include "shared/audio_pause.hpp"
// @ref ?queued_movies_00af8fd8@@3V?$DynamicVectorClass@PAVMovieHandle@@@@A=00af8fd8

bool Unknown_Movies_Queued_005a0ab0()
{
    return queued_movies_00af8fd8.Count() > 0;
}
