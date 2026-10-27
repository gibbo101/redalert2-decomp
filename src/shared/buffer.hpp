// Buffer: a pointer to a block of memory with its size and ownership.
//
// Layout from the constructors at 0x004382C0-0x004383D0 (Westwood's Buffer).
// A Buffer either references caller memory or allocates its own block (when
// given no pointer but a positive size); only owned blocks are deleted.
// Copies and assignments reference the source's memory without owning it.
#ifndef RA2_SHARED_BUFFER_HPP
#define RA2_SHARED_BUFFER_HPP

class Buffer {
public:
    Buffer(char *pointer, long size = 0);
    Buffer(void *pointer = 0, long size = 0);
    Buffer(void const *pointer, long size = 0);
    Buffer(long size);
    Buffer(Buffer const &buffer);
    ~Buffer();

    Buffer &operator=(Buffer const &buffer);

    // Releases an owned block and empties the buffer.
    void Reset();
    void *Get_Buffer() const { return BufferPtr; }
    long Get_Size() const { return Size; }
    bool Is_Valid() const { return BufferPtr != 0; }

protected:
    char *BufferPtr;        // +0x00 memory block (null when empty)
    long Size;              // +0x04 block size in bytes
    bool IsAllocated;       // +0x08 the block was allocated here and is owned
};

#endif
