// CacheStraw: a Straw that reads its source in large blocks.
//
// Name from RTTI (vtable 0x007A3BBC, base Straw): slot 0 scalar deleting
// destructor 0x00510AD0, slot 1 Straw::Get_From 0x0069B050, slot 2
// CacheStraw::Get 0x00494760. The default block size (4096) is the value
// INIClass::Load constructs it with.
#ifndef RA2_SHARED_CACHE_STRAW_HPP
#define RA2_SHARED_CACHE_STRAW_HPP

#include "shared/straw.hpp"
#include "shared/buffer.hpp"

class CacheStraw : public Straw {
public:
    CacheStraw(int size = 4096) : BufferPtr(size), Index(0), Length(0) {}
    virtual int Get(void *buffer, int length);

    Buffer BufferPtr;   // +0x0C cache block
    int Index;          // +0x18 next unread byte in the block
    int Length;         // +0x1C bytes held in the block
};

#endif
