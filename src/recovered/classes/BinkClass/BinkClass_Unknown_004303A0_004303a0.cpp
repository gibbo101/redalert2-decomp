// int BinkClass::Unknown_004303A0(int frame) (0x004303A0): BinkGoto(frame, 1).
#include "shared/movie.hpp"

int BinkClass::Unknown_004303A0(int frame)
{
    return BinkGoto(Handle, frame, 1);
}
