// Builds indexed or hicolor translation tables and registers the converter.
#define RGB_DECLARE_TO_HSV
#define CONVERT_DECLARE_DRAWERS
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ADD
#include "shared/hsv_class.hpp"
#include "shared/convert.hpp"
#include "shared/surface.hpp"
#include "shared/hicolor.hpp"
#include "shared/vector_class.hpp"

ConvertClass::ConvertClass(PaletteClass const &artpalette, PaletteClass const &screenpalette,
                          Surface *surface, int levels, bool quick)
    : BytesPerPixel(surface->Bytes_Per_Pixel()), 
      blit_plain_xlat_008(0), blit_trans_xlat_00c(0), blit_trans_darken_010(0), blit_trans_zremap_xlat_014(0),
      blit_trans_lucent75_018(0), blit_trans_lucent50_01c(0), blit_trans_lucent25_020(0), blit_plain_xlat_zread_024(0),
      blit_trans_xlat_zread_028(0), blit_trans_darken_zread_02c(0), blit_trans_zremap_xlat_zread_030(0), blit_trans_lucent75_zread_034(0),
      blit_trans_lucent50_zread_038(0), blit_trans_lucent25_zread_03c(0), blit_trans_lucent75_zread_warp_040(0), blit_trans_lucent50_zread_warp_044(0),
      blit_trans_lucent25_zread_warp_048(0), blit_plain_xlat_zread_write_04c(0), blit_trans_xlat_zread_write_050(0), blit_trans_darken_zread_write_054(0),
      blit_trans_zremap_xlat_zread_write_058(0), blit_trans_lucent75_zread_write_05c(0), blit_trans_lucent50_zread_write_060(0), blit_trans_lucent25_zread_write_064(0),
      blit_plain_xlat_alpha_068(0), blit_trans_xlat_alpha_06c(0), blit_trans_zremap_xlat_alpha_070(0), blit_trans_lucent75_alpha_074(0),
      blit_trans_lucent50_alpha_078(0), blit_trans_lucent25_alpha_07c(0), blit_trans_xlat_write_alpha_080(0), blit_trans_xlat_mult_write_alpha_084(0),
      blit_translucent_write_alpha_088(0), blit_translucent50_nonzero_alpha_08c(0), blit_translucent50_zero_alpha_090(0), blit_plain_xlat_alpha_094(0),
      blit_trans_xlat_alpha_zread_098(0), blit_trans_zremap_xlat_alpha_zread_09c(0), blit_trans_lucent75_alpha_zread_0a0(0), blit_trans_lucent50_alpha_zread_0a4(0),
      blit_trans_lucent25_alpha_zread_0a8(0), blit_trans_lucent75_alpha_zread_warp_0ac(0), blit_trans_lucent50_alpha_zread_warp_0b0(0), blit_trans_lucent25_alpha_zread_warp_0b4(0),
      blit_plain_xlat_alpha_0b8(0), blit_trans_xlat_alpha_zread_write_0bc(0), blit_trans_zremap_xlat_alpha_zread_write_0c0(0), blit_trans_lucent75_alpha_zread_write_0c4(0),
      blit_trans_lucent50_alpha_zread_write_0c8(0), blit_trans_lucent25_alpha_zread_write_0cc(0), rleblit_trans_xlat_0d0(0), rleblit_trans_darken_0d4(0),
      rleblit_trans_zremap_xlat_0d8(0), rleblit_trans_lucent75_0dc(0), rleblit_trans_lucent50_0e0(0), rleblit_trans_lucent25_0e4(0),
      rleblit_trans_xlat_zread_0e8(0), rleblit_trans_zremap_xlat_zread_0ec(0), rleblit_trans_darken_zread_0f0(0), rleblit_trans_lucent75_zread_0f4(0),
      rleblit_trans_lucent50_zread_0f8(0), rleblit_trans_lucent25_zread_0fc(0), rleblit_trans_lucent75_zread_warp_100(0), rleblit_trans_lucent50_zread_warp_104(0),
      rleblit_trans_lucent25_zread_warp_108(0), rleblit_trans_xlat_zread_write_10c(0), rleblit_trans_zremap_xlat_zread_write_110(0), rleblit_trans_darken_zread_write_114(0),
      rleblit_trans_lucent75_zread_write_118(0), rleblit_trans_lucent50_zread_write_11c(0), rleblit_trans_lucent25_zread_write_120(0), rleblit_trans_xlat_alpha_124(0),
      rleblit_trans_zremap_xlat_alpha_128(0), rleblit_trans_lucent75_alpha_12c(0), rleblit_trans_lucent50_alpha_130(0), rleblit_trans_lucent25_alpha_134(0),
      rleblit_trans_xlat_alpha_zread_138(0), rleblit_trans_zremap_xlat_alpha_zread_13c(0), rleblit_trans_lucent75_alpha_zread_140(0), rleblit_trans_lucent50_alpha_zread_144(0),
      rleblit_trans_lucent25_alpha_zread_148(0), rleblit_trans_lucent75_alpha_zread_warp_14c(0), rleblit_trans_lucent50_alpha_zread_warp_150(0), rleblit_trans_lucent25_alpha_zread_warp_154(0),
      rleblit_trans_xlat_alpha_zread_write_158(0), rleblit_trans_zremap_xlat_alpha_zread_write_15c(0), rleblit_trans_lucent75_alpha_zread_write_160(0), rleblit_trans_lucent50_alpha_zread_write_164(0),
      rleblit_trans_lucent25_alpha_zread_write_168(0),
      unknown_shadow_count(levels), AlphaPalette(0), Table(0), Remap(0), ActiveRemap(0)
{
    if (unknown_shadow_count < 1) unknown_shadow_count = 1;
    if (BytesPerPixel == 1) {
        Remap = new unsigned char[256];
        const_cast<unsigned char *>(Remap)[0] = 0;
        for (int index = 1; index < 256; ++index) {
            HSVClass hsv = artpalette[index];
            hsv.Value /= 2;
            RGBClass color = hsv.To_RGB();
            const_cast<unsigned char *>(Remap)[index] = (unsigned char)artpalette.Closest_Color(color);
        }
        AlphaPalette = new unsigned char[256 * unknown_shadow_count];
        unsigned char *translation = (unsigned char *)AlphaPalette;
        Table = translation + 256 * ((unknown_shadow_count - 1) >> 1);
        if (unknown_shadow_count == 1) {
            *translation++ = 0;
            for (int index = 1; index < 256; ++index) {
                *translation++ = (unsigned char)screenpalette.Closest_Color(artpalette[index]);
            }
        } else {
            for (int level = 0; level <= unknown_shadow_count - 1; ++level) {
                *translation++ = 0;
                for (int index = 1; index < 256; ++index) {
                    HSVClass hsv = artpalette[index];
                    hsv.Value = (unsigned char)((level * hsv.Value * 2) / (unknown_shadow_count - 1));
                    RGBClass color = hsv.To_RGB();
                    *translation++ = (unsigned char)screenpalette.Closest_Color(color);
                }
            }
        }
    } else {
        AlphaPalette = new unsigned short[256 * unknown_shadow_count];
        unsigned short *translation = (unsigned short *)AlphaPalette;
        Table = translation + 256 * ((unknown_shadow_count - 1) >> 1);
        if (!quick) Build_Brightness_Tables(translation, unknown_shadow_count, artpalette);
        HalfMask = unknown_half_mask_852fd0;
        QuarterMask = unknown_quarter_mask_852fd2;
    }
    if (!quick) Initialize_Blitters_00483B00();
    Drawers.Add(this);
}
