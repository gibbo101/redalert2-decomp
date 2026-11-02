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
#ifdef CONVERT_DECLARE_DRAWERS
template <class T> class DynamicVectorClass;
#endif

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

#ifdef CONVERT_DECLARE_DRAWERS
    // Every converter, so a display format change can rebuild them (0x00851150;
    // TibSun ConvertClass::Drawers; the constructor adds, the destructor deletes).
    // Guarded: the declaration shifts the _$E numbering of units that include
    // this header (populations 2498, 2967, 3302, 3462); convert.cpp defines the guard.
    static DynamicVectorClass<ConvertClass *> Drawers;
#endif

    int BytesPerPixel;              // +0x004
#ifdef CONVERT_NAMED_BLITTERS
    // Individually initialized pointers; array view retained for the indexed selectors.
    union {
        Blitter *Blitters[50];
        struct {
            Blitter *blit_plain_xlat_008;
            Blitter *blit_trans_xlat_00c;
            Blitter *blit_trans_darken_010;
            Blitter *blit_trans_zremap_xlat_014;
            Blitter *blit_trans_lucent75_018;
            Blitter *blit_trans_lucent50_01c;
            Blitter *blit_trans_lucent25_020;
            Blitter *blit_plain_xlat_zread_024;
            Blitter *blit_trans_xlat_zread_028;
            Blitter *blit_trans_darken_zread_02c;
            Blitter *blit_trans_zremap_xlat_zread_030;
            Blitter *blit_trans_lucent75_zread_034;
            Blitter *blit_trans_lucent50_zread_038;
            Blitter *blit_trans_lucent25_zread_03c;
            Blitter *blit_trans_lucent75_zread_warp_040;
            Blitter *blit_trans_lucent50_zread_warp_044;
            Blitter *blit_trans_lucent25_zread_warp_048;
            Blitter *blit_plain_xlat_zread_write_04c;
            Blitter *blit_trans_xlat_zread_write_050;
            Blitter *blit_trans_darken_zread_write_054;
            Blitter *blit_trans_zremap_xlat_zread_write_058;
            Blitter *blit_trans_lucent75_zread_write_05c;
            Blitter *blit_trans_lucent50_zread_write_060;
            Blitter *blit_trans_lucent25_zread_write_064;
            Blitter *blit_plain_xlat_alpha_068;
            Blitter *blit_trans_xlat_alpha_06c;
            Blitter *blit_trans_zremap_xlat_alpha_070;
            Blitter *blit_trans_lucent75_alpha_074;
            Blitter *blit_trans_lucent50_alpha_078;
            Blitter *blit_trans_lucent25_alpha_07c;
            Blitter *blit_trans_xlat_write_alpha_080;
            Blitter *blit_trans_xlat_mult_write_alpha_084;
            Blitter *blit_translucent_write_alpha_088;
            Blitter *blit_translucent50_nonzero_alpha_08c;
            Blitter *blit_translucent50_zero_alpha_090;
            Blitter *blit_plain_xlat_alpha_094;
            Blitter *blit_trans_xlat_alpha_zread_098;
            Blitter *blit_trans_zremap_xlat_alpha_zread_09c;
            Blitter *blit_trans_lucent75_alpha_zread_0a0;
            Blitter *blit_trans_lucent50_alpha_zread_0a4;
            Blitter *blit_trans_lucent25_alpha_zread_0a8;
            Blitter *blit_trans_lucent75_alpha_zread_warp_0ac;
            Blitter *blit_trans_lucent50_alpha_zread_warp_0b0;
            Blitter *blit_trans_lucent25_alpha_zread_warp_0b4;
            Blitter *blit_plain_xlat_alpha_0b8;
            Blitter *blit_trans_xlat_alpha_zread_write_0bc;
            Blitter *blit_trans_zremap_xlat_alpha_zread_write_0c0;
            Blitter *blit_trans_lucent75_alpha_zread_write_0c4;
            Blitter *blit_trans_lucent50_alpha_zread_write_0c8;
            Blitter *blit_trans_lucent25_alpha_zread_write_0cc;
        };
    };
#else
    Blitter *Blitters[50];          // +0x008 through +0x0CC
#endif
#ifdef CONVERT_NAMED_BLITTERS
    // Individually initialized pointers; array view retained for the indexed selectors.
    union {
        RLEBlitter *RLEBlitters[39];
        struct {
            RLEBlitter *rleblit_trans_xlat_0d0;
            RLEBlitter *rleblit_trans_darken_0d4;
            RLEBlitter *rleblit_trans_zremap_xlat_0d8;
            RLEBlitter *rleblit_trans_lucent75_0dc;
            RLEBlitter *rleblit_trans_lucent50_0e0;
            RLEBlitter *rleblit_trans_lucent25_0e4;
            RLEBlitter *rleblit_trans_xlat_zread_0e8;
            RLEBlitter *rleblit_trans_zremap_xlat_zread_0ec;
            RLEBlitter *rleblit_trans_darken_zread_0f0;
            RLEBlitter *rleblit_trans_lucent75_zread_0f4;
            RLEBlitter *rleblit_trans_lucent50_zread_0f8;
            RLEBlitter *rleblit_trans_lucent25_zread_0fc;
            RLEBlitter *rleblit_trans_lucent75_zread_warp_100;
            RLEBlitter *rleblit_trans_lucent50_zread_warp_104;
            RLEBlitter *rleblit_trans_lucent25_zread_warp_108;
            RLEBlitter *rleblit_trans_xlat_zread_write_10c;
            RLEBlitter *rleblit_trans_zremap_xlat_zread_write_110;
            RLEBlitter *rleblit_trans_darken_zread_write_114;
            RLEBlitter *rleblit_trans_lucent75_zread_write_118;
            RLEBlitter *rleblit_trans_lucent50_zread_write_11c;
            RLEBlitter *rleblit_trans_lucent25_zread_write_120;
            RLEBlitter *rleblit_trans_xlat_alpha_124;
            RLEBlitter *rleblit_trans_zremap_xlat_alpha_128;
            RLEBlitter *rleblit_trans_lucent75_alpha_12c;
            RLEBlitter *rleblit_trans_lucent50_alpha_130;
            RLEBlitter *rleblit_trans_lucent25_alpha_134;
            RLEBlitter *rleblit_trans_xlat_alpha_zread_138;
            RLEBlitter *rleblit_trans_zremap_xlat_alpha_zread_13c;
            RLEBlitter *rleblit_trans_lucent75_alpha_zread_140;
            RLEBlitter *rleblit_trans_lucent50_alpha_zread_144;
            RLEBlitter *rleblit_trans_lucent25_alpha_zread_148;
            RLEBlitter *rleblit_trans_lucent75_alpha_zread_warp_14c;
            RLEBlitter *rleblit_trans_lucent50_alpha_zread_warp_150;
            RLEBlitter *rleblit_trans_lucent25_alpha_zread_warp_154;
            RLEBlitter *rleblit_trans_xlat_alpha_zread_write_158;
            RLEBlitter *rleblit_trans_zremap_xlat_alpha_zread_write_15c;
            RLEBlitter *rleblit_trans_lucent75_alpha_zread_write_160;
            RLEBlitter *rleblit_trans_lucent50_alpha_zread_write_164;
            RLEBlitter *rleblit_trans_lucent25_alpha_zread_write_168;
        };
    };
#else
    RLEBlitter *RLEBlitters[39];     // +0x0D0 through +0x168
#endif
    int unknown_shadow_count;       // +0x16C
    void *AlphaPalette;             // +0x170
    void *Table;                    // +0x174 index -> surface value table
    unsigned char const *Remap;     // +0x178
    unsigned char const *ActiveRemap; // +0x17C
    unsigned int HalfMask;          // +0x180 (dword stores in the constructor)
    unsigned int QuarterMask;       // +0x184
};

#endif
