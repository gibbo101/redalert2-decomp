#include "shared/alpha_table_cache.hpp"
// Palette-index translation blitters. The byte-output class names are hypotheses
// from their operations and the RTTI-named ushort families; byte vtables are not retained.
#ifndef RA2_BASIC_XLAT_BLITTERS_HPP
#define RA2_BASIC_XLAT_BLITTERS_HPP
#include "shared/blitter.hpp"
template <class T>
class BlitPlainXlat : public Blitter {
public:
    BlitPlainXlat(T const * palette) : Palette(palette) {}

    virtual void BlitForward(void *target, void const *source, int length,
                             int, int, int, int, int) const;
    virtual void BlitBackward(void *target, void const *source, int length,
                              int, int, int, int) const;
    T const *Palette; // +0x04
};
template <class T>
class BlitTransXlat : public Blitter {
public:
    BlitTransXlat(T const * palette) : Palette(palette) {}

    virtual void BlitForward(void *target, void const *source, int length,
                             int, int, int, int, int) const;
    virtual void BlitBackward(void *target, void const *source, int length,
                              int, int, int, int) const;
    T const *Palette; // +0x04
};
template <class T>
class BlitTransZRemapXlat : public Blitter {
public:
    BlitTransZRemapXlat(unsigned char const *const * remap, T const * palette) : RemapTable(remap), Palette(palette) {}

    virtual void BlitForward(void *target, void const *source, int length,
                             int, int, int, int, int) const;
    virtual void BlitBackward(void *target, void const *source, int length,
                              int, int, int, int) const;
    unsigned char const *const *RemapTable; // +0x04
    T const *Palette; // +0x08
};
template <class T>
class BlitTransRemapXlat : public Blitter {
public:
    BlitTransRemapXlat(unsigned char const * remap, T const * palette) : RemapTable(remap), Palette(palette) {}

    virtual void BlitForward(void *target, void const *source, int length,
                             int, int, int, int, int) const;
    virtual void BlitBackward(void *target, void const *source, int length,
                              int, int, int, int) const;
    unsigned char const *RemapTable; // +0x04
    T const *Palette; // +0x08
};
#endif
