// int BinkMovieHandle::Unknown_Slot9() (0x005A1B50)
// Forwards to the Bink wrapper.
// @ref ?Unknown_004303C0@BinkClass@@QAEHXZ=004303c0
#include "shared/movie.hpp"

int BinkMovieHandle::Unknown_Slot9()
{
    return Bink->Unknown_004303C0();
}
