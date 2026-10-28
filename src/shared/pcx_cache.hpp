// The PCX image cache at 0x00A76378 (hypothesis: it loads the flag and
// background .pcx files by name, 0x0068CA40, and draws or writes them).
#ifndef RA2_SHARED_PCX_CACHE_HPP
#define RA2_SHARED_PCX_CACHE_HPP

#include "shared/rect.hpp"

class Surface;

class UnknownBitmapWriter {
public:
    UnknownBitmapWriter();                  // 0x0068BD50
    ~UnknownBitmapWriter();                 // 0x0068BE30
    void Write_0068c040(char const *file, void *bitmap, void *palette, int format);
    // Copies image into rect of destination, skipping the transparent pixel
    // (0x0068CE80; false when the image cannot be locked).
    bool Draw_0068ce80(Rect const &rect, Surface *destination, Surface *image, int transparent);
    // The image of a .pcx file, loaded on first use (0x0068CA40; arg2 meaning not recovered).
    Surface *Get_Image_0068ca40(char const *name, int arg2);
};
extern UnknownBitmapWriter unknown_bitmap_writer_a76378;

// The images the skirmish and multiplayer dialogs name (GDlgSupp.cpp): the
// country flags, [0] "rani.pcx" (random), [1] "obsi.pcx" (observer),
// [2..10] "usai.pcx" ... "rusi.pcx" (0x007F86B0), and three ping images
// "pingg.pcx", "pingy.pcx", "pingr.pcx" (0x007F86DC).
extern char const *unknown_flag_images_7f86b0[11];
extern char const *unknown_ping_images_7f86dc[3];

#endif
