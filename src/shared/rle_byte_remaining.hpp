#include "shared/alpha_table_cache.hpp"
#ifndef RA2_RLE_BYTE_REMAINING_HPP
#define RA2_RLE_BYTE_REMAINING_HPP
#include "shared/rle_blitter.hpp"
template <class T> class RLEBlitTransRemapDestZRead : public RLEBlitter {
public:
    RLEBlitTransRemapDestZRead(T const * palette) : Palette(palette) {}

 virtual void Blit(void *target, void const *source, int length, int skip, int depth, int depth_buffer, int, int, int, int adjustment) const;
 T const *Palette; // +4
};
template <class T> class RLEBlitTransRemapXlatZRead : public RLEBlitter {
public:
    RLEBlitTransRemapXlatZRead(unsigned char const * remap, T const * palette) : RemapTable(remap), Palette(palette) {}

 virtual void Blit(void *target, void const *source, int length, int skip, int depth, int depth_buffer, int, int, int, int adjustment) const;
 unsigned char const *RemapTable; // +4
 T const *Palette; // +8
};
template <class T> class RLEBlitTransRemapDestZReadWrite : public RLEBlitter {
public:
    RLEBlitTransRemapDestZReadWrite(T const * palette) : Palette(palette) {}

 virtual void Blit(void *target, void const *source, int length, int skip, int depth, int depth_buffer, int, int, int, int adjustment) const;
 T const *Palette; // +4
};
template <class T> class RLEBlitTransRemapXlatZReadWrite : public RLEBlitter {
public:
    RLEBlitTransRemapXlatZReadWrite(unsigned char const * remap, T const * palette) : RemapTable(remap), Palette(palette) {}

 virtual void Blit(void *target, void const *source, int length, int skip, int depth, int depth_buffer, int, int, int, int adjustment) const;
 unsigned char const *RemapTable; // +4
 T const *Palette; // +8
};
#endif
