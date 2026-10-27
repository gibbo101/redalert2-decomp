// void VQAClass::Unknown_0071CB20() (0x0071CB20): makes the movie palette current.
#include "shared/movie.hpp"
#include "shared/palette.hpp"
// @ref ?Set@PaletteClass@@QAEXXZ=00496120

void VQAClass::Unknown_0071CB20()
{
    ((PaletteClass *)Palette)->Set();
}
