// int VQMovieHandle::Unknown_Slot7(int unknown) (0x005A1910)
#include "shared/movie.hpp"

int VQMovieHandle::Unknown_Slot7(int unknown)
{
    Movie->Player->Unknown_0071D210();
    return Movie->Player->Unknown_0071CC60(unknown);
}
