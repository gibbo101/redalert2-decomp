// LCWPipe: a Pipe that LCW compresses or decompresses the data put into it.
//
// Name from RTTI (vtable 0x007A5464, base Pipe); methods in LCWPipe.cpp
// (0x00534EE0+). Data travels in blocks of at most BlockSize bytes, each
// preceded by a 4-byte header giving its compressed and uncompressed size.
#ifndef RA2_SHARED_LCW_PIPE_HPP
#define RA2_SHARED_LCW_PIPE_HPP

#include "shared/pipe.hpp"
#include "shared/lcw.hpp"

class LCWPipe : public Pipe {
public:
    // Direction of the data transformation.
    typedef enum CompControl {
        COMPRESS,
        DECOMPRESS
    } CompControl;

    LCWPipe(CompControl control, int blocksize);          // 0x00534EE0
    virtual ~LCWPipe();                                     // 0x00534F50
    virtual int Flush();                                    // 0x005351C0
    virtual int Put(void const *source, int length);        // 0x00534F90

    CompControl Control;    // +0x0C compressing or decompressing
    int Counter;            // +0x10 bytes accumulated in Buffer
    char *Buffer;           // +0x14 staging buffer for incoming data
    char *Buffer2;          // +0x18 output buffer for a processed block
    int BlockSize;          // +0x1C uncompressed bytes per block
    int SafetyMargin;       // +0x20 extra room for incompressible data

    struct {
        unsigned short CompCount;     // +0x24 compressed bytes (0xFFFF: header pending)
        unsigned short UncompCount;   // +0x26 uncompressed bytes
    } BlockHeader;
};

#endif
