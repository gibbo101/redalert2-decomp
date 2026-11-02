// StaticBufferClass::Entry *StaticBufferClass::Add(Surface &surface, Rect const &rect, int x, int y) (0x0069A300;
// no direct callers): the same for a rectangle stored with the point x, y.
#define STATIC_BUFFER_DECLARE_LIFETIME
#include "shared/rect.hpp"
#include "shared/surface_region.hpp"
#include "shared/static_buffer.hpp"
#include "shared/surface.hpp"
#include "shared/rle_engine.hpp"
#include "shared/crt_memory.hpp"

StaticBufferClass::Entry *StaticBufferClass::Add(Surface &surface, Rect const &rect, int x, int y)
{
    Entry *entry = (Entry *)Reserve(sizeof(Entry));
    if (entry == 0) {
        return 0;
    }
    entry->X = x;
    entry->Y = y;
    entry->Width = rect.Width;
    entry->Height = rect.Height;
    entry->Data = Current;
    unsigned char *source = (unsigned char *)surface.Lock(rect.Top_Left());
    RLEEngine rle;
    int line = 0;
    while (line < rect.Height) {
        int length = rle.Line_Compress(source, unknown_line_buffer_abd548, rect.Width);
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
