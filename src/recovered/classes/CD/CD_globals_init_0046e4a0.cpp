#define THEME_SOUND_CONTROLS
// CD.CPP dynamic initializer (0x0046E4A0)
// Constructs the unit's 16-byte static at 0x00850818 (four zeroed words).
// Its address sits in the C++ initializer table next to cdctrl.cpp's
// (0x0046EA40), which places it at the start of CD.CPP.
// Assumes: the object's type, layout and use are unknown (honest
// placeholder names).
#include "shared/cd.hpp"
// @ref ?unknown_static_850818@@3UUnknownStatic850818@@A=00850818

struct UnknownStatic850818 {
    UnknownStatic850818() : unknown_00(0), unknown_04(0), unknown_08(0), unknown_0C(0) {}
    int unknown_00;     // +0x00
    int unknown_04;     // +0x04
    int unknown_08;     // +0x08
    int unknown_0C;     // +0x0C
};

UnknownStatic850818 unknown_static_850818;     // 0x00850818
