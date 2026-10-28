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
};
extern UnknownBitmapWriter unknown_bitmap_writer_a76378;

#endif
