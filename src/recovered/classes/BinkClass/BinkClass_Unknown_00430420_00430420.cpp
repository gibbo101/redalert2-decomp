// bool BinkClass::Unknown_00430420() (0x00430420): the movie is past its last frame.
#include "shared/movie.hpp"

bool BinkClass::Unknown_00430420()
{
    return Handle->FrameNum >= Handle->Frames;
}
