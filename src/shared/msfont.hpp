// MSFont: the main-screen bitmap font (RTTI vtable 0x007A70B8, 5 slots;
// object 0x20 bytes from `new` at 0x0058FB29). Unit 0x005B3F20-0x005B468F
// (MSFont.cpp by the alphabetical link order: after MSEngine, before the
// message-box code at 0x005B4690).
//
// Glyphs are frames of FULLFNT3.SHP: character c (after CharToOemBuff) maps
// to frame (c - '!') * 3 + style, the index clamped to 0..0xD8; style 2 is
// used for widths. The palette SIDEFNT3.PAL / FULLFNT3.PAL is loaded into
// the palette at 0x00838710 and drawn through a ConvertClass. All fonts
// share one load: only the first constructed font loads, the destructor of
// the last one releases (instance count 0x00A71858).
//
// Evidenced: layout stores in the constructor/Load/destructor, slot
// behaviour, the strings. Names of methods, members and the unknown_
// globals are hypotheses.
#ifndef RA2_SHARED_MSFONT_HPP
#define RA2_SHARED_MSFONT_HPP

#include "shared/unknown_globals.hpp"
#include "shared/rect.hpp"
#include "shared/surface.hpp"
#include "shared/shape_file.hpp"
#include "shared/palette.hpp"

class MSFont {
public:
    MSFont(bool sidebar);                                               // 0x005B3F40
    virtual ~MSFont();                                                  // slot 0 (+0x00) 0x005B3F70
    virtual int Char_Width(unsigned short ch);                          // slot 1 (+0x04) 0x005B4300
    virtual int String_Width(unsigned short const *text);               // slot 2 (+0x08) 0x005B42A0
    virtual void Print(Surface *surface, unsigned short const *text, int x, int y, int style);      // slot 3 (+0x0C) 0x005B44F0
    virtual void Print_Char(Surface *surface, unsigned short ch, int x, int y, int style, int unknown6);  // slot 4 (+0x10) 0x005B43D0

    bool Load(bool sidebar);                                            // 0x005B3FD0
    void Text_Rect(unsigned short const *text, Rect &rect);             // 0x005B41F0

    int Width;                  // +0x04 shape width (widest glyph)
    int Height;                 // +0x08 shape height (line height)
    RGBClass Color;             // +0x0C palette entry 0x44
    int Pixel;                  // +0x10 Color in the screen pixel format
    ShapeFileStruct *Shape;     // +0x14 FULLFNT3.SHP
    ConvertClass *Drawer;       // +0x18
    bool OwnsShape;             // +0x1C Shape was loaded from a file, not a mixfile cache
};

// One of three file-local slots the last font destructor clears
// (0x00A71860, 8 bytes each); nothing else references them.
struct MSFontSlot {
    void *unknown_00;           // +0x00
    bool unknown_04;            // +0x04
};

extern int unknown_font_count_a71858;           // 0x00A71858 constructed fonts
extern MSFontSlot unknown_font_slots_a71860[3]; // 0x00A71860

extern PaletteClass unknown_palette_838710;     // 0x00838710

// Screen pixel format shifts (0x00852FB8-0x00852FCC): shared/hicolor.hpp.
#include "shared/hicolor.hpp"

#include "shared/sound_available.hpp"
#include "shared/debug_printf.hpp"
extern "C" unsigned int __cdecl wcslen(unsigned short const *string);   // 0x00783605

extern "C" __declspec(dllimport) int __stdcall CharToOemBuffA(char const *source, char *dest, unsigned long length);

#endif
