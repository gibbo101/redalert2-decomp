// PaletteClass::PaletteClass(unsigned char *binary_palette) (0x00603020): the 768 raw bytes copied in.
#include "shared/convert.hpp"
#include "shared/crt_memory.hpp"

PaletteClass::PaletteClass(unsigned char *binary_palette)
{
    memcpy(&Palette[0], binary_palette, sizeof(Palette));
}
