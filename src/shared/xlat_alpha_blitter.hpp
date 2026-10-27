#include "shared/alpha_table_cache.hpp"
// BlitTransXlatWriteAlpha<unsigned short>: RTTI-named alpha/depth-value writer.
#ifndef RA2_XLAT_ALPHA_BLITTER_HPP
#define RA2_XLAT_ALPHA_BLITTER_HPP
#include "shared/blitter.hpp"
template <class T>
class BlitTransXlatWriteAlpha : public Blitter {
public:
    BlitTransXlatWriteAlpha() {}

    virtual void BlitForward(void *target, void const *source, int length,
                             int level, int unknown5, int buffer, int unknown7, int unknown8) const;
    virtual void BlitBackward(void *target, void const *source, int length,
                              int a, int b, int c, int d) const {
        BlitForward(target, source, length, a, b, c, d, 0);
    }
};
#endif
