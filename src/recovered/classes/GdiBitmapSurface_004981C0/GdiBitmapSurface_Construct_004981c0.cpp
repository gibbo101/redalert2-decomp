// Allocate an 8-bit Windows DIB and a BSurface over its pixel backing.
#include "shared/gdi_bitmap_surface.hpp"
#include "shared/convert.hpp"
#include "shared/surface.hpp"
#include "shared/crt_memory.hpp"
GdiBitmapSurface_004981C0::GdiBitmapSurface_004981C0(HWND window, int width, int height, PaletteClass const &palette)
    : Error(false), Info(0), Bitmap(0), Bits(0), Width(width), Height(height), Origin(0), Stride(0), BackingSurface(0)
{
    Info = (BITMAPINFO *)new unsigned char[sizeof(BITMAPINFO) + 256 * sizeof(RGBQUAD)];
    if (Info) {
        Info->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        Info->bmiHeader.biWidth = width;
        Info->bmiHeader.biHeight = (int)(0u - (unsigned int)height);
        Info->bmiHeader.biPlanes = 1;
        Info->bmiHeader.biBitCount = 8;
        Info->bmiHeader.biCompression = 0;
        Info->bmiHeader.biSizeImage = 0;
        Info->bmiHeader.biXPelsPerMeter = 0;
        Info->bmiHeader.biYPelsPerMeter = 0;
        Info->bmiHeader.biClrUsed = 256;
        Info->bmiHeader.biClrImportant = 256;
        for (int index = 0; index < 256; ++index) {
            Info->bmiColors[index].rgbBlue = palette[index].Blue;
            Info->bmiColors[index].rgbGreen = palette[index].Green;
            Info->bmiColors[index].rgbRed = palette[index].Red;
            Info->bmiColors[index].rgbReserved = 0;
        }
        HDC dc = GetDC(window);
        Bitmap = CreateDIBSection(dc, Info, 0, &Bits, 0, 0);
        ReleaseDC(window, dc);
        if (Bitmap) {
            Width = Info->bmiHeader.biWidth;
            Height = abs(Info->bmiHeader.biHeight);
            int pitch = (int)(((unsigned int)Width + 3u) & ~3u);
            Stride = pitch;
            if (Info->bmiHeader.biHeight > 0) {
                Origin = (unsigned char *)Bits + ((unsigned int)Height - 1u) * (unsigned int)Width;
                pitch = (int)(0u - (unsigned int)pitch);
            } else {
                Origin = (unsigned char *)Bits;
            }
            Stride = pitch;
            int backing_width = abs(pitch);
            BackingSurface = new BSurface(backing_width, Height, 1, Bits);
            if (BackingSurface) return;
        }
    }
    Error = true;
}
