// StaticBufferClass::Entry *StaticBufferClass::Add(Surface &surface, SurfaceRegion const &region) (0x0069A1D0; the
// techno voxel draws 0x006D2xxx): appends an Entry header (point, size, data start) and the region's lines RLE
// compressed through the static line buffer 0x00ABD548; null (and nothing kept past the failure) when full. The
// line counter steps before the stride call (a while loop); Reserve tests the end before taking Current.
#define STATIC_BUFFER_DECLARE_LIFETIME
#include "shared/rect.hpp"
#include "shared/surface_region.hpp"
#include "shared/static_buffer.hpp"
#include "shared/surface.hpp"
#include "shared/rle_engine.hpp"
#include "shared/crt_memory.hpp"
// @ref ?unknown_line_buffer_abd548@@3PAEA=00abd548
// @ref ?Top_Left@Rect@@QBE?AURectPoint2D@@XZ=00435560
extern unsigned char unknown_line_buffer_abd548[];     // 0x00ABD548 one compressed line

StaticBufferClass::Entry *StaticBufferClass::Add(Surface &surface, SurfaceRegion const &region)
{
    Entry *entry = (Entry *)Reserve(sizeof(Entry));
    if (entry == 0) {
        return 0;
    }
    entry->X = region.Point.X;
    entry->Y = region.Point.Y;
    entry->Width = region.Bounds.Width;
    entry->Height = region.Bounds.Height;
    entry->Data = Current;
    unsigned char *source = (unsigned char *)surface.Lock(region.Bounds.Top_Left());
    RLEEngine rle;
    int line = 0;
    while (line < region.Bounds.Height) {
        int length = rle.Line_Compress(source, unknown_line_buffer_abd548, region.Bounds.Width);
        unsigned char *dest = Reserve(length);
        if (dest == 0) {
            surface.Unlock();
            return 0;
        }
        memcpy(dest, unknown_line_buffer_abd548, length);
        line++;
        source += surface.Stride();
    }
    surface.Unlock();
    return entry;
}
