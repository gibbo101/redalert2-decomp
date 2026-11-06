// The PCX image cache at 0x00A76378 (hypothesis: it loads the flag and
// background .pcx files by name, 0x0068CA40, and draws or writes them).
#ifndef RA2_SHARED_PCX_CACHE_HPP
#define RA2_SHARED_PCX_CACHE_HPP

#include "shared/rect.hpp"

class Surface;

#ifdef PCX_CACHE_DECLARE_IMAGES
#include "shared/wol_dictionary.hpp"

// Declared only in units that define PCX_CACHE_DECLARE_IMAGES (the cache's own unit, 0x0068BC50-0x0068D94F):
// a new declaration here renumbers the compiler labels of the fragile Refresh_Wonline_Players 0x0073FEE0.
// One cached image: the surface read from the file and the palette read with it (dictionary value, 0x304 bytes).
struct UnknownBitmapEntry {
    UnknownBitmapEntry() : Image(0) {}
    Surface *Image;
    unsigned char Palette[768];
};
#endif

class UnknownBitmapWriter {
public:
    UnknownBitmapWriter();                  // 0x0068BD50
    ~UnknownBitmapWriter();                 // 0x0068BE30
    void Write_0068c040(char const *file, void *bitmap, void *palette, int format);
#ifdef PCX_CACHE_DECLARE_UNLOAD
    // Removes the image of name from the cache and deletes it (0x0068CB30; no caller found, name hypothesis).
    void Unload_Image_0068cb30(char const *name);
#endif
#ifdef PCX_CACHE_DECLARE_DRAWS
    // Tiles 16-bit image pixels over destination rect, with source x/y offsets (0x0068CCE0).
    bool Draw_0068cce0(Rect const &rect, Surface *destination, Surface *image, int source_x, int source_y);
#endif
    // Copies image into rect of destination, skipping the transparent pixel
    // (0x0068CE80; false when the image cannot be locked).
    bool Draw_0068ce80(Rect const &rect, Surface *destination, Surface *image, int transparent);
    // The image of a .pcx file, loaded on first use (0x0068CA40; arg2 meaning not recovered).
    Surface *Get_Image_0068ca40(char const *name, int arg2);
#ifdef PCX_CACHE_DECLARE_LOADS
    // Declared only in units that define PCX_CACHE_DECLARE_LOADS: any new declaration here renumbers the
    // compiler labels of Refresh_Wonline_Players 0x0073FEE0 (a fragile row) and changes its code.
    // Loads a .pcx file into the cache under its lower-case name, replacing a cached image of that name
    // (0x0068C600): arg2 2 converts it to a 16-bit surface, arg2 1 keeps the palette and, with arg3, replaces
    // each pixel by its palette colour's red value. False when the file cannot be read.
    bool Load_Image_0068c600(char const *name, int arg2, int arg3);
    // Load_Image_0068c600(name, 1, 1) (0x0068CA20, not yet recovered).
    void Load_Image_0068ca20(char const *name);
#endif
    // Draws image through its alpha image into rect of destination with the palette, from x offset
    // source_x of the image (0x0068CF90; the other arguments are 0 in every caller seen).
    bool Draw_0068cf90(Rect const &rect, Surface *destination, Surface *image, Surface *alpha, unsigned char *palette,
                       int arg6, int source_x, int arg8);

#ifdef PCX_CACHE_DECLARE_IMAGES
    // The loaded images by file name (Hash_Name rotating hash; sizeof 0x38).
    WolDictionary<Wstring, UnknownBitmapEntry> Images;      // +0x00
#endif
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
