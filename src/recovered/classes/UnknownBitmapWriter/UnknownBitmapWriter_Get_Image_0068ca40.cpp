// Surface *UnknownBitmapWriter::Get_Image_0068ca40(char const *name, int arg2) (0x0068CA40)
// The cached image of name (0 when it is not loaded); arg2, when not 0, receives its 768-byte palette.
#include "shared/pcx_cache.hpp"
// @ref _?$S4@?1??Get_Image_0068ca40@UnknownBitmapWriter@@QAEPAVSurface@@PBDH@Z@4EA=00abd0e0
// @ref _?entry@?1??Get_Image_0068ca40@UnknownBitmapWriter@@QAEPAVSurface@@PBDH@Z@4UUnknownBitmapEntry@@A=00abd0e8
// @ref _$E5=0068cb20

Surface *UnknownBitmapWriter::Get_Image_0068ca40(char const *name, int arg2)
{
    Wstring key(name);
    static UnknownBitmapEntry entry;
    entry.Image = 0;
    if (!Images.Get_Value(key, entry)) return 0;
    if (arg2) memcpy((void *)arg2, entry.Palette, sizeof(entry.Palette));
    return entry.Image;
}
