// BufferClass: a block of memory that is either the caller's or allocated and
// owned here (Westwood's WIN32LIB BufferClass; TibSun buffer.cpp).
//
// Unit 0x00438470-0x004384F0 (after Buffer's Buffer.cpp): the constructors
// 0x00438470, 0x004384B0, 0x004384D0 and the destructor 0x004384E0 have no
// direct callers. Not the RA-style Buffer of shared/buffer.hpp.
#ifndef RA2_SHARED_BUFFER_CLASS_HPP
#define RA2_SHARED_BUFFER_CLASS_HPP

class BufferClass {
public:
    BufferClass(void *ptr, int size);   // 0x00438470
    BufferClass(int size);              // 0x004384B0
    BufferClass();                      // 0x004384D0
    ~BufferClass();                     // 0x004384E0

    void *Get_Buffer() { return Buffer; }
    int Get_Size() { return Size; }

private:
    BufferClass(BufferClass const &);
    BufferClass &operator=(BufferClass const &);

    unsigned char *Buffer;  // +0x00
    int Size;               // +0x04
    bool Allocated;         // +0x08 the block was allocated here
};

#endif
