// void VQAClass::Unknown_0071CAF0(unsigned char const *palette) (0x0071CAF0)
// Copies the 768-byte palette and marks it changed.
#include "shared/movie.hpp"
#include "shared/crt_memory.hpp"

void VQAClass::Unknown_0071CAF0(unsigned char const *palette)
{
    memcpy(Palette, palette, sizeof(Palette));
    PaletteChanged = true;
}
