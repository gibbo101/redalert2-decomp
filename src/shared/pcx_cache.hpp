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
#ifdef PCX_CACHE_DECLARE_LOADS
    // Declared only in units that define PCX_CACHE_DECLARE_LOADS: any new declaration here renumbers the
    // compiler labels of Refresh_Wonline_Players 0x0073FEE0 (a fragile row) and changes its code.
    // Loads a .pcx file into the cache (0x0068C600, not yet recovered; argument meanings not recovered).
    int Load_Image_0068c600(char const *name, int arg2, int arg3);
    // Load_Image_0068c600(name, 1, 1) (0x0068CA20, not yet recovered).
    void Load_Image_0068ca20(char const *name);
#endif
    // Draws image through its alpha image into rect of destination with the palette, from x offset
    // source_x of the image (0x0068CF90; the other arguments are 0 in every caller seen).
    void Draw_0068cf90(Rect const &rect, Surface *destination, Surface *image, Surface *alpha, unsigned char *palette,
                       int arg6, int source_x, int arg8);
};
extern UnknownBitmapWriter unknown_bitmap_writer_a76378;
// Brightens a 768-byte RGB palette: red and green by 1.5, clamped to 255 (0x0068BCE0; hypothesis).
void __fastcall unknown_brighten_palette_68bce0(unsigned char *palette);

// The images the skirmish and multiplayer dialogs name (GDlgSupp.cpp): the
// country flags, [0] "rani.pcx" (random), [1] "obsi.pcx" (observer),
// [2..10] "usai.pcx" ... "rusi.pcx" (0x007F86B0), and three ping images
// "pingg.pcx", "pingy.pcx", "pingr.pcx" (0x007F86DC).
extern char const *unknown_flag_images_7f86b0[11];
extern char const *unknown_ping_images_7f86dc[3];

#endif
