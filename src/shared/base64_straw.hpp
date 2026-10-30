// Base64Straw: a straw that Base64-encodes or decodes the data drawn through
// it (Westwood's B64STRAW.H).
//
// Name from RTTI (vtable 0x007A3BCC, base Straw): slot 0 scalar deleting
// destructor 0x00510B00, slot 1 Straw::Get_From 0x0069B050, slot 2
// Base64Straw::Get 0x0042B850. INIClass::Put_UUBlock (0x0050CFC0) encodes
// with one.
#ifndef RA2_SHARED_BASE64_STRAW_HPP
#define RA2_SHARED_BASE64_STRAW_HPP

#include "shared/straw.hpp"

class Base64Straw : public Straw {
public:
    enum CodeControl {
        ENCODE,
        DECODE
    };

    Base64Straw(CodeControl control) : Control(control), Counter(0) {}
    virtual int Get(void *source, int slen);

private:
    CodeControl Control;    // +0x0C
    int Counter;            // +0x10 bytes held in the buffer being filled
    char CBuffer[4];        // +0x14 coded bytes
    char PBuffer[3];        // +0x18 plain bytes
};

#endif
