// LZOPipe: a Pipe that LZO compresses or decompresses the data put into it.
//
// Name from RTTI (vtable 0x007A58B4, base Pipe); methods in LZOPipe.cpp
// (0x0053EB40+). Same block format as LCWPipe: each block is preceded by a
// 4-byte header giving its compressed and uncompressed size.
#ifndef RA2_SHARED_LZO_PIPE_HPP
#define RA2_SHARED_LZO_PIPE_HPP

#include "shared/pipe.hpp"
#include "shared/lzo.hpp"

class LZOPipe : public Pipe {
public:
    // Direction of the data transformation.
    typedef enum CompControl {
        COMPRESS,
        DECOMPRESS
    } CompControl;

    LZOPipe(CompControl control, int blocksize);            // 0x0053EB40
    virtual ~LZOPipe();                                     // 0x0053EBA0
    virtual int Flush();                                    // 0x0053EE70
    virtual int Put(void const *source, int length);        // 0x0053EBE0

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
