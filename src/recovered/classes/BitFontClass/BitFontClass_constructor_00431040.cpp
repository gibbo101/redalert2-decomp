// Missing_Glyph 0x00431F50 is declared for this unit (Draw_Char 0x004318E0 expands it).
#define RA2_BITFONT_MISSING_GLYPH
// BitFontClass::BitFontClass(char const *filename) (0x00431040)
// Starts from the defaults, then takes the font file's glyph data and
// metrics (the defaults again when it cannot be loaded).
#include "shared/text_print.hpp"
#include "shared/win32_api.hpp"
// @ref ??_7BitFontClass@@6B@=0079c788
// @ref __imp__SetRect@20=0079a4a8
// @ref ?Load_Font_Data@BitFontClass@@SIPAUFontDataType@@PBD@Z=00431150
// @ref ?unknown_431ec0@BitFontClass@@QAEXXZ=00431ec0

inline void BitFontClass::Reset()
{
    Data = 0;
    Color = 0x7FFF;
    unknown_26 = 0x3555;
    unknown_28 = 0x40;
    unknown_40 = 1;
    Clipping = 1;
    Width = 1;
    Height = 1;
    unknown_20 = 0;
    Buffer = 0;
    unknown_08 = 0;
    SetRect((RECT *)&ClipBox, 0, 0, 0, 0);
    unknown_2c = 1;
}

// Never expanded inline in its unit (BitTextClass calls it).
#pragma auto_inline(off)
BitFontClass::BitFontClass(char const *filename)
{
    Reset();
    if (!Load_Font(filename)) {
        Reset();
    }
}
#pragma auto_inline(on)
