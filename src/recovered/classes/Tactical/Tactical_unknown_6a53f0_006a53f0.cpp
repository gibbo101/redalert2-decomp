// void Tactical::Unknown_006A53F0(wchar_t const *text, int value) -- 0x006A53F0
// Purpose: sets the view's text (+0x24) and value (+0xA4); a null text
// clears both first (the clear is 0x006A5440, expanded inline).
// Assumptions: Tactical (0x0083996C, shared/gscreen.hpp's stand-in) is
// declared here only with these members; their meaning (a caption shown by
// the view, e.g. for House.cpp's callers at 0x004E805D) is not identified.

extern "C" unsigned short *__cdecl wcscpy(unsigned short *dest, unsigned short const *source);   // 0x00783689
// @ref _wcscpy=00783689

class Tactical {
public:
    void Unknown_006A53F0(unsigned short const *text, int value);
    void Unknown_006A5440()
    {
        unknown_a4 = -1;
        unknown_24[0] = 0;
    }

    char unknown_00[0x24];
    unsigned short unknown_24[64];      // +0x24
    int unknown_a4;                     // +0xA4
};

void Tactical::Unknown_006A53F0(unsigned short const *text, int value)
{
    if (text == 0) {
        Unknown_006A5440();
    } else {
        wcscpy(unknown_24, text);
    }
    unknown_a4 = value;
}
