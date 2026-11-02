// PaletteClass &PaletteClass::operator=(PaletteClass const &) (0x00603080).
#include "shared/convert.hpp"
#include "shared/crt_memory.hpp"

PaletteClass &PaletteClass::operator=(PaletteClass const &palette)
{
    if (this == &palette) return *this;

    memcpy(&Palette[0], &palette.Palette[0], sizeof(Palette));
    return *this;
}
