// Text printing helpers (unit 0x00497340-0x0049819F): text rectangles, the
// Simple/Fancy text printers (bit font 0x0084E9E8, printer 0x0084E9D0),
// formatted and tabbed variants, Draw_Box (0x004973D0) and the font
// accessor (0x00497A50). Westwood names (Simple_Text_Print,
// Fancy_Text_Print, Conquer_Clip_Text_Print) are hypotheses for RA2's
// wide-character versions; flag bits: 0x100 centre, 0x200 right, 0x400
// opaque background, 0x8000 translucent shadow box.
//
// Overlaps to merge: shared/ms_anim.hpp (unknown_bit_font_84e9e8,
// unknown_bit_printer_84e9d0), shared/font_message_views.hpp (FontDrawState:
// line height +0x1C, clip box +0x30), shared/color_scheme.hpp (ColorScheme, HSVClass), shared/gscreen.hpp
// (unknown_surface_83995c). ConvertClass is shared/convert.hpp's and the
// pixel shifts are shared/hicolor.hpp's.
// The Gadgets copy of gadget.hpp includes this header in place of its
// UnknownFont stand-in.
#ifndef RA2_SHARED_TEXT_PRINT_HPP
#define RA2_SHARED_TEXT_PRINT_HPP

#include "shared/unknown_globals.hpp"
#include "shared/rect.hpp"
#include "shared/rgb_class.hpp"
#include "shared/convert.hpp"
#include "shared/hicolor.hpp"
#include "shared/surface.hpp"
#include "shared/crt_memory.hpp"
#include "shared/color_scheme.hpp"
// Inline element access only (ColorSchemes[index]).
#ifndef VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#endif
#include "shared/vector_class.hpp"

#ifndef _WCHAR_T_DEFINED
typedef unsigned short wchar_t;
#define _WCHAR_T_DEFINED
#endif

#include "shared/tag_rect.hpp"

// The bitmap font text is drawn with (the object at 0x0084E9E8 points to).
// The glyph data of a font file (0x24 bytes; Load_Font_Data 0x00431150).
// "fonT" files store the header directly, "FoNt" files a header, a table
// of character ranges and the glyphs.
struct FontDataType {
    int unknown_00;                     // +0x00
    int Width;                          // +0x04 (BitFontClass::Width)
    int unknown_08;                     // +0x08
    int Height;                         // +0x0C (BitFontClass::Height)
    int GlyphCount;                     // +0x10
    int GlyphSize;                      // +0x14 bytes per glyph
    unsigned short *Map;                // +0x18 character -> glyph number + 1 (0x10000 entries)
    unsigned char *Glyphs;              // +0x1C GlyphCount * GlyphSize bytes
    int MappedCount;                    // +0x20 characters with a glyph
};

// One character range of a "FoNt" file (12 bytes).
struct FontRangeType {
    unsigned short First;               // +0x00 glyph number before the range's first glyph
    unsigned short unknown_02;
    int Low;                            // +0x04 first character
    int High;                           // +0x08 last character
};

// "FoNt" file header (0x24 bytes).
struct FontFileHeaderType {
    int Magic;                          // +0x00 'FoNt'
    int unknown_04;
    int Width;                          // +0x08
    int unknown_0c;
    int Height;                         // +0x10
    int RangeCount;                     // +0x14
    int GlyphSize;                      // +0x18
    int RangeOffset;                    // +0x1C
    int GlyphOffset;                    // +0x20
};

// RTTI class name BitFont (vtable 0x0079C788: the deleting destructor).
class BitFontClass {
public:
    BitFontClass(char const *filename);                                             // 0x00431040
    virtual ~BitFontClass();                                                        // 0x00431100
    static FontDataType *__fastcall Load_Font_Data(char const *filename);           // 0x00431150
    static void __fastcall Free_Font_Data(FontDataType *data);                      // 0x004313C0
    void Reset();                                                                   // (inline in the constructor's unit)
    bool Load_Font(char const *filename);                                           // 0x004313F0
    unsigned char *Glyph_Data(wchar_t character) const;                             // 0x00431E80 (width byte, then the bitmap)
    void unknown_431ec0();                                                          // 0x00431EC0 (inverted copy of 'X' in unknown_08)
    void unknown_431f70();                                                          // 0x00431F70 (one pixel taller, space one wider)
    void unknown_431fa0();                                                          // 0x00431FA0 (one pixel taller, U+3000 twice the space)
    bool Intersect_Rect(tagRECT *result, tagRECT const *a, tagRECT const *b);      // 0x00432000 (empty 0,0,-1,-1 when they do not meet)
    void Set_Surface(Surface *surface);                                             // 0x004320B0 (locks it; clip box defaults to it)
    void Release_Surface(Surface *surface);                                         // 0x00432150 (unlocks it)
    void Set_unknown_20(int value);                                                 // 0x004318D0
    int Draw_Char(wchar_t character, int x, int y, int arg4);                       // 0x004318E0
    int Draw_String(wchar_t const *text, int x, int y, int arg4, int arg5);         // 0x00431CC0
    unsigned short Set_Color(unsigned short color);                                 // 0x00431430 (returns the old one)
    unsigned char Set_Clipping(unsigned char clip);                                 // 0x00431450 (returns the old one)
    void Set_Clip_Box(tagRECT const *box);                                          // 0x00431460
    bool Get_Text_Area(wchar_t const *text, int *width, int *height, int max_width);   // 0x004314B0 (false without font or text; name hypothesis)
    int String_Pixel_Width(wchar_t const *string, int arg2) const;                  // 0x00431690
    int Chars_In_Width(wchar_t const *string, int width, int arg3, int arg4) const;  // 0x00431710 (how many characters of string fit in width; name hypothesis)
    int Char_Pixel_Width(wchar_t character) const;                                  // 0x00432170

    FontDataType *Data;     // +0x04
    void *unknown_08;       // +0x08 (released with free)
    void *Buffer;           // +0x0C the locked surface (Set_Surface)
    unsigned Pitch;         // +0x10 in pixels
    int unknown_14;
    int Width;              // +0x18
    int Height;             // +0x1C line height
    int unknown_20;         // +0x20
    unsigned short Color;   // +0x24 packed text colour (Set_Color)
    unsigned short unknown_26;
    int unknown_28;         // +0x28 tab width (shared/font_message_views.hpp; hypothesis)
    int unknown_2c;         // +0x2C spacing (hypothesis)
    tagRECT ClipBox;        // +0x30 (Set_Clip_Box)
    unsigned char unknown_40;
    unsigned char Clipping; // +0x41 raw clipping flag (Set_Clipping)
    unsigned char unknown_42[2];
    // size 0x44 (font_message_views.hpp's FontDrawState view)
};
extern BitFontClass *BitFont;               // 0x0084E9E8

// The bitmap text printer (the object at 0x0084E9D0 points to).
// RTTI class name BitText (vtable 0x0079C790): owns the game font.
class BitTextClass {
public:
    BitTextClass();                                                                 // 0x00432290 (loads GAME.FNT into BitFont)
    virtual ~BitTextClass();                                                        // 0x004322D0
    int Print_Char(BitFontClass *font, Surface *surface, wchar_t character, int x, int y);   // 0x00432300
    int Print(BitFontClass *font, Surface *surface, wchar_t const *text, int x, int y,
              int arg6, int arg7);                                                  // 0x00432350
    bool Print_Box(BitFontClass *font, Surface *surface, wchar_t const *text, int x, int y, int width, int height,
                   int arg8, int arg9, int arg10);                                  // 0x00432490 (text in a box; true when drawn)
    int Print_Bold(BitFontClass *font, Surface *surface, wchar_t const *text, int x, int y, int count);   // 0x004323B0 (twice, one pixel apart, when the font's unknown_40 is set)
    bool Print_Box_Shadow(BitFontClass *font, Surface *surface, wchar_t const *text, int x, int y, int width,
                          int height, int arg8, int arg9, int arg10);               // 0x00432B00 (in unknown_26, one pixel down-right, then in the colour)
    bool Print_Box_Bold(BitFontClass *font, Surface *surface, wchar_t const *text, int x, int y, int width,
                        int height, int arg8, int arg9, int arg10);                 // 0x00432BB0 (twice, one pixel apart, when the font's unknown_40 is set)
    void Load_Game_Font();                                                          // 0x00432C90 (as the constructor)
    void Free_Game_Font();                                                          // 0x00432CC0 (as the destructor)
    void Free_Font(BitFontClass *font);                                             // 0x00432CF0 (clears BitFont when it is the game font)
};
extern BitTextClass *BitText;               // 0x0084E9D0

// HSVClass: shared/hsv_class.hpp.

// The palette converter: shared/convert.hpp (ConvertClass::Convert).

// ColorScheme and ColorSchemes: shared/color_scheme.hpp.

// Screen pixel format shifts: shared/hicolor.hpp.

// The surface the GUI draws on (as shared/gscreen.hpp).

// The index of the colour scheme boxes are drawn in (0x004CEFC0, outside this unit).
int unknown_scheme_index_4cefc0();

// A 16-byte buffer of the unit (0x00852480).
extern unsigned char unknown_buffer_852480[16];

extern "C" int __cdecl vswprintf(unsigned short *buffer, unsigned short const *format, char *arguments);   // 0x00783A58
extern "C" unsigned short *__cdecl wcscpy(unsigned short *dest, unsigned short const *source);           // 0x00783689
extern "C" unsigned short *__cdecl wcschr(unsigned short const *string, unsigned short character);       // 0x00783AC6

Rect __fastcall Text_Rect(wchar_t const *text, int x, int y, unsigned flags, int padx, int pady);   // 0x00497360
void __fastcall Draw_Box(Rect const &rect, int style, bool fill);                       // 0x004973D0
int __fastcall Text_Lines(wchar_t const *text, int style, int columns, int *width, int *height);   // 0x004977D0
Point2D __fastcall Simple_Text_Print(wchar_t const *text, Surface *surface, Rect const *clip, Point2D *xy,
                                     unsigned fore, unsigned back, unsigned flags, int unknown8 = 1);   // 0x00497830
Point2D __fastcall Fancy_Text_Print(wchar_t const *text, Surface *surface, Rect const *clip, Point2D *xy,
                                    ColorScheme *scheme, unsigned back, unsigned flags, int unknown8 = 1);   // 0x00497990
BitFontClass *__fastcall Font_For_Style(int style);                                     // 0x00497A50
Point2D __cdecl Plain_Text_Print(wchar_t const *format, Surface *surface, Rect const *clip, Point2D *xy,
                                 unsigned fore, unsigned back, unsigned flags, ...);    // 0x00497A60
Point2D __cdecl Fancy_Text_Printf(wchar_t const *format, Surface *surface, Rect const *clip, Point2D *xy,
                                  ColorScheme *scheme, unsigned back, unsigned flags, ...);   // 0x00497B40
Point2D __fastcall Conquer_Clip_Text_Print(wchar_t const *text, Surface *surface, Rect const *clip,
                                           Point2D *xy, unsigned fore, unsigned back, unsigned flags,
                                           unsigned width, int const *tabs);      // 0x00497CE0
Point2D __fastcall Fancy_Clip_Text_Print(wchar_t const *text, Surface *surface, Rect const *clip,
                                         Point2D *xy, ColorScheme *scheme, unsigned back, unsigned flags,
                                         unsigned width, int const *tabs);        // 0x00497E80
// Simple_Text_Print in colour scheme `scheme` (an index into ColorSchemes),
// or in `fore` when scheme is -1. Two identical copies (0x00497F40,
// 0x00498050); names are placeholders.
Point2D __fastcall unknown_scheme_text_print_497f40(wchar_t const *text, Surface *surface, Rect const *clip,
                                                    Point2D *xy, unsigned fore, unsigned back, unsigned flags,
                                                    int scheme, int unknown8);   // 0x00497F40
Point2D __fastcall unknown_scheme_text_print_498050(wchar_t const *text, Surface *surface, Rect const *clip,
                                                    Point2D *xy, unsigned fore, unsigned back, unsigned flags,
                                                    int scheme, int unknown8);   // 0x00498050
unsigned char *__fastcall unknown_fill_buffer_498160(int value);              // 0x00498160

// Simple_Text_Print in the base colour of a colour scheme: the inline form
// Fancy_Text_Printf (0x00497B40) and the indexed printers (0x00497F40,
// 0x00498050) expand. It does what Fancy_Text_Print (0x00497990) does, but
// its channels are combined green, blue, red; the out-of-line function's
// red, green, blue order does not reproduce the inlined copies, nor this one
// the out-of-line function.
inline Point2D Scheme_Text_Print(wchar_t const *text, Surface *surface, Rect const *clip, Point2D *xy,
                                 ColorScheme *scheme, unsigned back, unsigned flags, int unknown8)
{
    RGBClass color = scheme->BaseColor.To_RGB();
    unsigned pixel = ((color.Green >> unknown_shift_852fcc) << unknown_shift_852fc8)
                   | ((color.Blue >> unknown_shift_852fc4) << unknown_shift_852fc0)
                   | ((color.Red >> unknown_shift_852fbc) << unknown_shift_852fb8);
    return Simple_Text_Print(text, surface, clip, xy, pixel, back, flags, unknown8);
}

#endif
