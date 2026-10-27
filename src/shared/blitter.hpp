// Blitter: a pixel-run copier used by Bit_Blit (Westwood's blitter.h).
//
// Names from RTTI: Blitter (vtable 0x0079E52C: destructor and two pure
// slots), BlitPlain<T> and BlitTrans<T> for T = unsigned char / unsigned
// short (vtables 0x007AFC94 / 0x007AFC84 and 0x007AFCB4 / 0x007AFCA4).
// The objects hold only the vtable pointer. The template members are
// emitted with xsurface.cpp (0x00775980-0x00775B30), which instantiates them.
#ifndef RA2_SHARED_BLITTER_HPP
#define RA2_SHARED_BLITTER_HPP

#include "shared/crt_memory.hpp"

class Surface;
class Rect;

class Blitter {
public:
    virtual ~Blitter() {}
    // Copies length pixels from source to target, first to last. The four
    // middle arguments and the last flag are unused by the plain and
    // transparent blitters (their meaning is not established).
    virtual void BlitForward(void *target, void const *source, int length,
                             int unknown4, int unknown5, int unknown6, int unknown7, int unknown8) const = 0;
    // The same for overlapping memory (copies last to first where it matters).
    virtual void BlitBackward(void *target, void const *source, int length,
                              int unknown4, int unknown5, int unknown6, int unknown7) const = 0;
};

// Copies every pixel.
template <class T>
class BlitPlain : public Blitter {
public:
    virtual void BlitForward(void *target, void const *source, int length,
                             int, int, int, int, int) const
    {
        memcpy(target, source, length * sizeof(T));
    }
    virtual void BlitBackward(void *target, void const *source, int length,
                              int, int, int, int) const
    {
        memmove(target, source, length * sizeof(T));
    }
};

// Copies all but colour 0 (transparent).
// BlitTrans<unsigned char>::BlitForward (0x00775980) is handwritten
// assembly in the original and is declared, not defined, here.
template <class T>
class BlitTrans : public Blitter {
public:
    virtual void BlitForward(void *target, void const *source, int length,
                             int unknown4, int unknown5, int unknown6, int unknown7, int unknown8) const;
    virtual void BlitBackward(void *target, void const *source, int length,
                              int unknown4, int unknown5, int unknown6, int unknown7) const
    {
        BlitForward(target, source, length, unknown4, unknown5, unknown6, unknown7, 0);
    }
};

template <class T>
void BlitTrans<T>::BlitForward(void *target, void const *source, int length,
                               int, int, int, int, int) const
{
    for (int index = 0; index < length; index++) {
        T color = *(T const *)source;
        source = (T const *)source + 1;
        if (color != 0) {
            *(T *)target = color;
        }
        target = (T *)target + 1;
    }
}

// The 8-bit transparent copy is handwritten assembly (0x00775980).
template <>
void BlitTrans<unsigned char>::BlitForward(void *target, void const *source, int length,
                                           int, int, int, int, int) const;

// Copies sourcerect of source to destrect of dest through blitter
// (0x00434AE0). The four trailing arguments are passed as 0, 3, 1000, 0 by
// every surface copy; their meaning is not established.
bool __fastcall Bit_Blit(Surface &dest, Rect const &destrect, Surface &source, Rect const &sourcerect,
                         Blitter const &blitter, int unknown1, int unknown2, int unknown3, int unknown4);

// Bit_Blit with the plain or the transparent (colour 0 skipped) blitter for
// dest's pixel size (0x00775560 / 0x007755C0; names are hypotheses). Small
// enough for VC6 to expand them inline into the surface copies.
bool __fastcall Bit_Blit_Plain(Surface &dest, Rect const &destrect, Surface &source, Rect const &sourcerect);
bool __fastcall Bit_Blit_Trans(Surface &dest, Rect const &destrect, Surface &source, Rect const &sourcerect);

#endif
