// void BinkClass::Unknown_004307E0() (0x004307E0): marks the next frame due (BinkWait 0).
#include "shared/movie.hpp"

void BinkClass::Unknown_004307E0()
{
    if (BinkWait(Handle) == 0) {
        unknown_2d = true;
    }
}
