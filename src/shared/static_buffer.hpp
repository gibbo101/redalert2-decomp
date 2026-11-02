// The voxel draw cache's static buffer (moved from shared/voxel_cache.hpp so its definition needs no
// other header).
#ifndef RA2_SHARED_STATIC_BUFFER_HPP
#define RA2_SHARED_STATIC_BUFFER_HPP

class Surface;
struct SurfaceRegion;
class Rect;

class StaticBufferClass {
public:
    // Cached image header: signed screen offsets, unsigned dimensions, RLE data.
    struct Entry {
        short X;
        short Y;
        unsigned short Width;
        unsigned short Height;
        unsigned char *Data;
    };
#ifdef STATIC_BUFFER_DECLARE_LIFETIME
    // Declared only for the definition of unknown_voxel_static_buffer_839aa0 (other includers keep
    // the implicit members).
    StaticBufferClass(int size);            // 0x0069A1A0
    ~StaticBufferClass();                   // 0x0069A1C0
#endif
    // Appends the region's pixels RLE-compressed line by line behind an Entry header; null when the
    // buffer is full (0x0069A1D0).
    Entry *Add(Surface &surface, SurfaceRegion const &region);
#ifdef STATIC_BUFFER_DECLARE_LIFETIME
    // The same for a rectangle drawn at point (0x0069A300).
    Entry *Add(Surface &surface, Rect const &rect, int x, int y);
    // Reserves size bytes at Current (null when they do not fit).
    unsigned char *Reserve(int size)
    {
        if (Current + size > Buffer + Capacity) {
            return 0;
        }
        unsigned char *pointer = Current;
        Current += size;
        return pointer;
    }
#endif
    int Capacity;               // +0x00 (the constructor stores the size first)
    unsigned char *Buffer;      // +0x04
    unsigned char *Current;     // +0x08
};
extern StaticBufferClass unknown_voxel_static_buffer_839aa0;

#endif
