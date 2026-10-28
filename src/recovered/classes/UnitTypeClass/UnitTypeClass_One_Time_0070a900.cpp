// void UnitTypeClass::One_Time() (0x0070A900)
// Makes the shared drawing resources once: a 256x256 byte surface cleared to 0, a drawer converting
// unknown_palette_837e10 onto it, and the small and large visceroid shapes.
#include "shared/unit_type.hpp"
#include "shared/surface.hpp"
#include "shared/convert.hpp"
#include "shared/mix_file_class.hpp"
#include "shared/cc_file_class.hpp"
#include "shared/unknown_globals.hpp"

// @ref ?unknown_surface_ad0604@@3PAVBSurface@@A=00ad0604
// @ref ?unknown_drawer_ad0608@@3PAVConvertClass@@A=00ad0608
// @ref ?VisceroidSmallShape@@3PBXB=00ad060c
// @ref ?VisceroidLargeShape@@3PBXB=00ad0610
// @ref ?unknown_palette_837e10@@3VPaletteClass@@A=00837e10
// @ref ??_C@_0N@CGM@VISC_SML?4SHP?$AA@=007f901c
// @ref ??_C@_0N@KIFF@VISC_LRG?4SHP?$AA@=007f900c

void UnitTypeClass::One_Time()
{
    if (unknown_surface_ad0604 == 0) {
        unknown_surface_ad0604 = new BSurface(256, 256, 1);
        unknown_surface_ad0604->Fill(0);
    }
    if (unknown_drawer_ad0608 == 0) {
        unknown_drawer_ad0608 = new ConvertClass(unknown_palette_837e10, unknown_palette_837e10, unknown_surface_ad0604, 1, false);
    }
    VisceroidSmallShape = MixFileClass<CCFileClass>::Retrieve("VISC_SML.SHP");
    VisceroidLargeShape = MixFileClass<CCFileClass>::Retrieve("VISC_LRG.SHP");
}
