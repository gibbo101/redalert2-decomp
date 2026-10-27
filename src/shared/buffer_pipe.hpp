// Original type name and base proved by RTTI; only the observed prefix is modelled.
// No allocation size, complete class extent, construction or destructor implementation is claimed.
#ifndef RA2_SHARED_BUFFERPIPE_HPP
#define RA2_SHARED_BUFFERPIPE_HPP
#include "shared/pipe.hpp"
#include "shared/buffer.hpp"
class BufferPipe : public Pipe {
public:
    virtual int Put(void const *source,int length);
private:
    Buffer Storage; // +0x0C: pointer/size/ownership from real Buffer
    int Position;   // +0x18: transferred-byte position
};
#endif
