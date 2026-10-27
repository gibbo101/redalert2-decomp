// Original type name and base proved by RTTI; only the observed prefix is modelled.
// No allocation size, complete class extent, construction or destructor implementation is claimed.
#ifndef RA2_SHARED_BUFFERSTRAW_HPP
#define RA2_SHARED_BUFFERSTRAW_HPP
#include "shared/straw.hpp"
#include "shared/buffer.hpp"
class BufferStraw : public Straw {
public:
    BufferStraw(void *buffer, int length) : Storage(buffer, length), Position(0) {}
    virtual int Get(void *destination,int length);
private:
    Buffer Storage; // +0x0C: pointer/size/ownership from real Buffer
    int Position;   // +0x18: transferred-byte position
};
#endif
