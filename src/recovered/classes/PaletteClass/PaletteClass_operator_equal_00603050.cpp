// bool PaletteClass::operator==(PaletteClass const &) const (0x00603050).
#include "shared/convert.hpp"
#include "shared/crt_memory.hpp"

bool PaletteClass::operator==(PaletteClass const &palette) const
{
    if (this == &palette) return true;
    return memcmp(&Palette[0], &palette.Palette[0], sizeof(Palette)) == 0;
}
