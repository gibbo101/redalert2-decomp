// BinkClass::BinkClass(char const *filename, Surface *surface) (0x0042FEA0)
// Opens the movie to play onto `surface`.
#include "shared/movie.hpp"

BinkClass::BinkClass(char const *filename, Surface *surface) :
    unknown_00(false),
    Handle(0),
    Target(surface),
    Companion(0),
    File(INVALID_HANDLE_VALUE),
    unknown_2c(true),
    unknown_2d(false)
{
    Open(filename);
}
