// Base64Pipe: a pipe that Base64-encodes or decodes the data put through it
// (Westwood's B64PIPE.H).
//
// Name from RTTI (vtable 0x007A3BDC, base Pipe): slot 0 scalar deleting
// destructor 0x00510B40, slot 1 Base64Pipe::Flush 0x0042B800, slot 2
// Pipe::End 0x0046CB80, slot 3 Pipe::Put_To 0x0060EAA0, slot 4
// Base64Pipe::Put 0x0042B670. INIClass::Get_UUBlock (0x0050D0F0) decodes
// with one.
#ifndef RA2_SHARED_BASE64_PIPE_HPP
#define RA2_SHARED_BASE64_PIPE_HPP

#include "shared/pipe.hpp"

class Base64Pipe : public Pipe {
public:
    enum CodeControl {
        ENCODE,
        DECODE
    };

    Base64Pipe(CodeControl control) : Control(control), Counter(0) {}
    virtual int Flush();
    virtual int Put(void const *source, int slen);

private:
    CodeControl Control;    // +0x0C
    int Counter;            // +0x10 bytes held in the buffer being filled
    char CBuffer[4];        // +0x14 coded bytes
    char PBuffer[3];        // +0x18 plain bytes
};

#endif
