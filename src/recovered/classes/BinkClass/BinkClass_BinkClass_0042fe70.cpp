// BinkClass::BinkClass(char const *filename) (0x0042FE70)
// Opens the movie for the default target (chosen by Open).
#include "shared/movie.hpp"

BinkClass::BinkClass(char const *filename) :
    unknown_00(false),
    Handle(0),
    Target(0),
    Companion(0),
    File(INVALID_HANDLE_VALUE),
    unknown_2c(true),
    unknown_2d(false)
{
    Open(filename);
}
