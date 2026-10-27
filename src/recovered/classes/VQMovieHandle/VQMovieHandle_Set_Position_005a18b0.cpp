// void VQMovieHandle::Set_Position(int x, int y) (0x005A18B0)
// Moves the frame; the destination follows the source rectangle.
#include "shared/movie.hpp"

void VQMovieHandle::Set_Position(int x, int y)
{
    Movie->Source.X = x;
    Movie->Source.Y = y;
    Movie->Dest = Movie->Source;
}
