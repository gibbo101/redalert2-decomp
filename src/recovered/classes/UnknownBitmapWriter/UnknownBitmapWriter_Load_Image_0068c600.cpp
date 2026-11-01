// bool UnknownBitmapWriter::Load_Image_0068c600(char const *name, int arg2, int arg3) (0x0068C600)
// Reads the .pcx file name into the cache under its lower-case name, replacing (and deleting) an image
// already cached under it. arg2 2 converts the image to a 16-bit surface through the screen pixel format;
// arg2 1 keeps the 8-bit image with its palette, and with arg3 set replaces each pixel by its palette
// colour's red value. False when the file cannot be read.
// The unit's shape helpers fall back to its one static rectangle (0x0068BC50), like AnimType.cpp.
#include "shared/unknown_static_rect.hpp"
#define SHAPE_FILE_EMPTY_RECT unknown_static_rect
#include "shared/pcx_cache.hpp"
#include "shared/surface.hpp"
#include "shared/cc_file_class.hpp"
#include "shared/convert.hpp"
#include "shared/hicolor.hpp"
#include "shared/ms_anim.hpp"
// @ref ?Grow_Table@?$WolDictionary@VWstring@@UUnknownBitmapEntry@@@@QAEXXZ=0068d8a0
// @ref ?Remove_Entry@?$WolDictionary@VWstring@@UUnknownBitmapEntry@@@@QAE_NABVWstring@@PAUUnknownBitmapEntry@@@Z=0068d540

bool UnknownBitmapWriter::Load_Image_0068c600(char const *name, int arg2, int arg3)
{
    int index;
    PaletteClass palette;
    UnknownBitmapEntry entry;
    CCFileClass file(name);
    Surface *pcx = unknown_load_pcx_60d110(&file, (int)&palette, 0, 0);
    Surface *image = pcx;
    if (pcx == 0) return false;

    if (arg2 == 2) {
        unsigned short table[256];
        for (index = 0; index < 256; index++) {
            table[index] = Build_Hicolor_Pixel(palette.Palette[index].Red, palette.Palette[index].Green, palette.Palette[index].Blue);
        }
        Rect rect = pcx->Get_Rect();
        image = new BSurface(rect.Width, rect.Height, 2);
        unsigned short *destination = (unsigned short *)image->Lock();
        unsigned char *source = (unsigned char *)pcx->Lock();
        for (index = 0; index < rect.Width * rect.Height; index++) {
            destination[index] = table[source[index]];
        }
        pcx->Unlock();
        image->Unlock();
        delete pcx;
    } else if (arg2 == 1) {
        memcpy(entry.Palette, &palette, sizeof(entry.Palette));
    }
    if (arg3 && arg2 == 1) {
        Rect rect = image->Get_Rect();
        unsigned char *pixels = (unsigned char *)image->Lock();
        for (index = 0; index < rect.Width * rect.Height; index++) {
            pixels[index] = palette.Palette[pixels[index]].Red;
        }
        image->Unlock();
    }
    entry.Image = image;

    Wstring key(name);
    key.To_Lower();
    UnknownBitmapEntry old;
    if (Images.Get_Value(key, old)) {
        Images.Remove(key);
        delete old.Image;
    }
    Images.Add(key, entry);
    return true;
}
