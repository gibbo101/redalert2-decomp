// UnknownBitmapWriter::~UnknownBitmapWriter() (0x0068BE30): deletes every cached image, then the dictionary.
#include "shared/pcx_cache.hpp"
#include "shared/surface.hpp"
// @ref ?Shrink_Table@?$WolDictionary@VWstring@@UUnknownBitmapEntry@@@@QAEXXZ=0068d7f0

UnknownBitmapWriter::~UnknownBitmapWriter()
{
    Wstring name;
    UnknownBitmapEntry entry;
    while (Images.Remove_Any(name, entry)) {
        delete entry.Image;
    }
}
