// The voxel draw cache's static buffer (moved from shared/voxel_cache.hpp so its definition needs no
// other header).
#ifndef RA2_SHARED_STATIC_BUFFER_HPP
#define RA2_SHARED_STATIC_BUFFER_HPP

class Surface;
struct SurfaceRegion;

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
    Entry *Add(Surface &surface, SurfaceRegion const &region);
    unsigned char *Buffer;
    int Capacity;
    unsigned char *Current;
};
extern StaticBufferClass unknown_voxel_static_buffer_839aa0;

#endif
