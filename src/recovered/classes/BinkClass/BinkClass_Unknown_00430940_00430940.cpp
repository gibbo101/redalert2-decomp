// void BinkClass::Unknown_00430940(Surface *surface, int x, int y) (0x00430940)
// Copies the current frame into `surface` at x, y again (with the companion
// areas cleared first and drawn after).
#include "shared/movie.hpp"
// @ref ?Unknown_00430A30@BinkClass@@QAEXPAVSurface@@@Z=00430a30
// @ref ?Unknown_00430AF0@BinkClass@@QAEXPAVSurface@@@Z=00430af0

void BinkClass::Unknown_00430940(Surface *surface, int x, int y)
{
    Unknown_00430AF0(surface);
    void *buffer = surface->Lock();
    if (buffer != 0) {
        int pitch = surface->Stride();
        int height = surface->Get_Height();
        BinkCopyToBuffer(Handle, buffer, pitch, height, x, y, SurfaceType | 0x80000000);
        surface->Unlock();
    }
    Unknown_00430A30(surface);
}
