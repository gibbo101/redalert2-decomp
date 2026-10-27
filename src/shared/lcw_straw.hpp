// LCWStraw: a Straw that LCW compresses or decompresses the data drawn
// through it.
//
// Name from RTTI (vtable 0x007A547C, base Straw); methods in LCWStraw.cpp
// (0x005352D0+). Same block format as LCWPipe.
#ifndef RA2_SHARED_LCW_STRAW_HPP
#define RA2_SHARED_LCW_STRAW_HPP

#include "shared/straw.hpp"
#include "shared/lcw.hpp"

class LCWStraw : public Straw {
public:
    // Direction of the data transformation.
    typedef enum CompControl {
        COMPRESS,
        DECOMPRESS
    } CompControl;

    LCWStraw(CompControl control, int blocksize);          // 0x005352D0
    virtual ~LCWStraw();                                    // 0x00535340
    virtual int Get(void *buffer, int length);              // 0x00535380

    CompControl Control;    // +0x0C compressing or decompressing
    int Counter;            // +0x10 processed bytes still to hand out
    char *Buffer;           // +0x14 uncompressed block
    char *Buffer2;          // +0x18 compressed block with header (compress only)
    int BlockSize;          // +0x1C uncompressed bytes per block
    int SafetyMargin;       // +0x20 extra room for incompressible data

    struct {
        unsigned short CompCount;     // +0x24 compressed bytes
        unsigned short UncompCount;   // +0x26 uncompressed bytes
    } BlockHeader;
};

#endif
