// void UnknownBitmapWriter::Unload_Image_0068cb30(char const *name) (0x0068CB30)
// Removes the cached image of name, if any, and deletes its surface (no caller found: name hypothesis).
#include "shared/pcx_cache.hpp"
#include "shared/surface.hpp"
// @ref ?Shrink_Table@?$WolDictionary@VWstring@@UUnknownBitmapEntry@@@@QAEXXZ=0068d7f0

// Takes one image out of the dictionary and deletes its surface.
inline void Remove_Image(WolDictionary<Wstring, UnknownBitmapEntry> &images, Wstring const &key)
{
    UnknownBitmapEntry entry;
    if (images.Get_Value(key, entry)) {
        images.Remove(key);
        delete entry.Image;
    }
}

void UnknownBitmapWriter::Unload_Image_0068cb30(char const *name)
{
    Wstring key(name);
    Remove_Image(Images, key);
}
