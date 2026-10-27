// UnknownBuffer_0069A1A0::UnknownBuffer_0069A1A0(int size) -- 0x0069A1A0
// Purpose: a buffer of `size` bytes: records the size and starts both the
// read and the write position at the new storage.
// Assumptions: owner and field names are hypotheses.
// @ref ??2@YAPAXI@Z=00782017

struct UnknownBuffer_0069a1a0 {
    UnknownBuffer_0069a1a0(int size);
    int Size;                               // +0x00
    char *Head;                             // +0x04
    char *Tail;                             // +0x08
};

UnknownBuffer_0069a1a0::UnknownBuffer_0069a1a0(int size)
{
    Size = size;
    char *data = new char[size];
    Head = data;
    Tail = data;
}
