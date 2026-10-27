// Release palette storage, the DIB handle, then the BSurface object.
#include "shared/gdi_bitmap_surface.hpp"
#include "shared/surface.hpp"
GdiBitmapSurface_004981C0::~GdiBitmapSurface_004981C0()
{
    if (Info) delete[] (unsigned char *)Info;
    if (Bitmap) DeleteObject(Bitmap);
    if (BackingSurface) delete BackingSurface;
}
