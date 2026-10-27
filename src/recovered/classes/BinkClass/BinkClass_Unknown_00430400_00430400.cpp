// void BinkClass::Unknown_00430400(bool pause) (0x00430400): BinkPause.
#include "shared/movie.hpp"

void BinkClass::Unknown_00430400(bool pause)
{
    BinkPause(Handle, pause);
}
