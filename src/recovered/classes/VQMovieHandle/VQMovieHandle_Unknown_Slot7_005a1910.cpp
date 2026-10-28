// void VQMovieHandle::Unknown_Slot7(int frame) (0x005A1910)
// Seeks the VQA player to a frame (0x0071D210, then 0x0071CC60).
#include "shared/movie.hpp"

void VQMovieHandle::Unknown_Slot7(int frame)
{
    Movie->Player->Unknown_0071D210();
    Movie->Player->Unknown_0071CC60(frame);
}
