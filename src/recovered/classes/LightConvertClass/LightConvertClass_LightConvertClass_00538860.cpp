// LightConvertClass::LightConvertClass(...) (0x00538860)
// A tinted converter: ConvertClass, the palettes, the light colour (current and stored), then the tint for a
// scenario that has shadow levels.
#include "shared/light_convert.hpp"
#include "shared/id_source.hpp"
#include "shared/hicolor.hpp"
// @ref ??0ConvertClass@@QAE@ABVPaletteClass@@0PAVSurface@@H_N@Z=00483650
// @ref ?Initialize_Blitters_00483B00@ConvertClass@@QAEXXZ=00483b00
// @ref ?Set_Tint@LightConvertClass@@UAEXHHH_N@Z=00538aa0
// @ref ?Get_Unknown_7d6290@@YAHXZ=004abb90
// @ref ?Unknown_0051FC50@@YA_NXZ=0051fc50
// @ref ?Unknown_0051FC60@@YA_NXZ=0051fc60
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref ?unknown_7d6290@@3HA=007d6290
// @ref ??_7LightConvertClass@@6B@=007a55dc
// @ref ??_GLightConvertClass@@UAEPAXI@Z=00538f30
// @ref ??_ELightConvertClass@@UAEPAXI@Z=00538f30
bool Unknown_0051FC50();
bool Unknown_0051FC60();
extern "C" unsigned char DAT_007df768[];
extern "C" int DAT_007df868;

LightConvertClass::LightConvertClass(PaletteClass const &artpalette, PaletteClass const &screenpalette, Surface *surface,
                                     int red, int green, int blue, bool skip_blitters, unsigned char const *remap,
                                     int unknown_shadow_count)
    : ConvertClass(artpalette, screenpalette, surface, unknown_shadow_count, true),
      ArtPalette(&artpalette), ScreenPalette(&screenpalette), unknown_190(remap), unknown_194(0),
      Red(red), Green(green), Blue(blue), StoredRed(red), StoredGreen(green), StoredBlue(blue), unknown_1b0(false)
{
    if (this->unknown_shadow_count >= 1) {
        if (remap == 0) {
            unknown_190 = DAT_007df768;
        }
        if (DAT_007df868 == -1) {
            DAT_007df868 = Get_Unknown_7d6290();
        }
        if (Unknown_0051FC50()) {
            if (red == -1) {
                Red = 1000;
                Green = 1000;
                Blue = 1000;
            } else {
                Red = red;
                Green = green;
                Blue = blue;
            }
            Set_Tint(unknown_id_source_a3d290->IonRed * 1000 / 100, unknown_id_source_a3d290->IonGreen * 1000 / 100,
                     unknown_id_source_a3d290->IonBlue * 1000 / 100, true);
        } else if (Unknown_0051FC60()) {
            if (red == -1) {
                Red = 1000;
                Green = 1000;
                Blue = 1000;
            } else {
                Red = red;
                Green = green;
                Blue = blue;
            }
            Set_Tint(unknown_id_source_a3d290->unknown_22e4 * 1000 / 100, unknown_id_source_a3d290->unknown_22e8 * 1000 / 100,
                     unknown_id_source_a3d290->unknown_22ec * 1000 / 100, true);
        } else {
            Set_Tint(red, green, blue, false);
        }
        if (!skip_blitters) {
            Initialize_Blitters_00483B00();
        }
    }
}
