// PaletteClass and ConvertClass: a 256-colour palette and Westwood's palette
// converter (0x188 bytes; constructor 0x00483650, destroyed through vtable
// slot 0). Split from shared/palette.hpp so the text printers and the sidebar
// can use them without palette.hpp's shape_file.hpp (whose header static
// would join every gadget unit).
#ifndef RA2_SHARED_CONVERT_HPP
#define RA2_SHARED_CONVERT_HPP

#include "shared/rgb_class.hpp"

class Surface;
class Blitter;
class RLEBlitter;

class PaletteClass {
public:
    RGBClass &operator[](int index) { return Palette[index % 256]; }
    RGBClass const &operator[](int index) const { return Palette[index % 256]; }
    PaletteClass &operator=(PaletteClass const &palette);   // 0x00603080

    // Makes this the current palette (0x00496120; a copy into 0x00851CC8
    // when it is not that palette already; name is a hypothesis).
    void Set();
    // Adjusts the entries whose lookup flag is set toward palette by
    // ratio/256 (0x00603160; Westwood's PaletteClass::Partial_Adjust).
    void Partial_Adjust(int ratio, PaletteClass const &palette, bool *lookup);

    int Closest_Color(RGBClass const &color) const; // 0x006031B0

    RGBClass Palette[256];  // +0x000
};

class ConvertClass {
public:
    ConvertClass(PaletteClass const &artpalette, PaletteClass const &screenpalette, Surface *surface,
                 int unknown_shadow_count, bool unknown5);           // 0x00483650
    virtual ~ConvertClass();                                         // slot 0

    // The surface value of palette index `color`: a byte table for 8-bit
    // surfaces, a word table otherwise (Draw_Box 0x004973D0).
    int Convert(int color) const
    {
        if (BytesPerPixel == 1) {
            return ((unsigned char const *)Table)[color];
        }
        return ((unsigned short const *)Table)[color];
    }

    void Initialize_Blitters_00483B00();
    Blitter *Select_Blitter_00485AA0(unsigned flags);
    // RLE selector; logical const in the reference, with lazy blitter initialization.
    RLEBlitter const *RLEBlitter_From_Flags_00485d60(unsigned flags) const;
    void Delete_Blitters_004853A0();                                 // 0x004853A0

    int BytesPerPixel;              // +0x004
    Blitter *Blitters[50];          // +0x008 through +0x0CC
    RLEBlitter *RLEBlitters[39];     // +0x0D0 through +0x168
    int unknown_shadow_count;       // +0x16C
    void *AlphaPalette;             // +0x170
    void *Table;                    // +0x174 index -> surface value table
    unsigned char const *Remap;     // +0x178
    unsigned char const *ActiveRemap; // +0x17C
    unsigned short HalfMask;        // +0x180
    unsigned short unknown_182;     // +0x182
    unsigned short QuarterMask;     // +0x184
    unsigned short unknown_186;     // +0x186
};

#endif
