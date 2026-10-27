// bool __fastcall unknown_can_send_chat(UnknownFlags_0073c0b0 const *flags, WideString const &text) -- 0x0073C0B0
// Purpose: a WOL chat permission test: false without flags; true when its
// first bit is set or either dialog 0xC2 or 0xC9 is open; otherwise,
// depending on whether text is plain 8-bit text, whether 0x00B2A7E8 or
// 0x00B2A804 is set.
// Assumptions: the flags object and the two globals are unidentified; the
// function name is a guess from the WOL chat callers' area.
// @ref ?Unknown_00735940@@YIPAXH@Z=00735940
// @ref ?Is_ASCII@WideString@@QBE_NXZ=00771080
// @ref ?unknown_b2a7e8@@3HA=00b2a7e8
// @ref ?unknown_b2a804@@3HA=00b2a804

struct UnknownFlags_0073c0b0 {
    unsigned char Bits;
};

class WideString {
public:
    bool Is_ASCII() const;      // 0x00771080

private:
    unsigned short *Buffer;
};

void *__fastcall Unknown_00735940(int id);  // 0x00735940 (a dialog by id)
extern int unknown_b2a7e8;
extern int unknown_b2a804;

bool __fastcall unknown_can_send_chat(UnknownFlags_0073c0b0 const *flags, WideString const &text)
{
    if (flags == 0) {
        return false;
    }
    if (flags->Bits & 1) {
        return true;
    }
    if (Unknown_00735940(0xC2) != 0) {
        return true;
    }
    if (Unknown_00735940(0xC9) != 0) {
        return true;
    }
    if (text.Is_ASCII()) {
        return unknown_b2a7e8 != 0;
    }
    return unknown_b2a804 != 0;
}
