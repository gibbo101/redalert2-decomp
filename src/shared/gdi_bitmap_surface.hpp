// Nonpolymorphic DIB-section owner at004981C0. Original class name unknown.
// Observed layout prefix from the full constructor, cleanup and clear operations.
// Fields extend through+0x20; the complete wrapper allocation extent is unknown.
#ifndef RA2_GDI_BITMAP_SURFACE_HPP
#define RA2_GDI_BITMAP_SURFACE_HPP
#include "shared/win32_gdi.hpp"
class BSurface;
class PaletteClass;
class GdiBitmapSurface_004981C0 {
public:
    GdiBitmapSurface_004981C0(HWND window, int width, int height, PaletteClass const &palette);
    ~GdiBitmapSurface_004981C0();
    void Clear(unsigned char color);
    bool Error;                  // +00
    BITMAPINFO *Info;             // +04 allocation sizeofBITMAPINFO+256RGBQUADs
    HBITMAP Bitmap;               // +08 owned DIB handle
    void *Bits;                  // +0C DIB pixel backing
    int Width, Height;           // +10,+14 logical pixel dimensions
    unsigned char *Origin;       // +18 logical first row (bottom-up case adjusted)
    int Stride;                  // +1C signed padded row stride
    BSurface *BackingSurface;    // +20 owns a surface over Bits, widthabsStride
};
#endif
