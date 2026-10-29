// 0x00520B00: tints every light converter, the converters of the colour
// schemes with +0x310 above 1 and those of the colour-scheme lists
// (0x00520A80, inline) to red, green, blue (thousandths; -1 for the scenario
// ambient), then refreshes every map cell.
#include "shared/lightning_storm.hpp"
#include "shared/color_scheme.hpp"
#include "shared/light_convert.hpp"
#include "shared/map_view.hpp"
// @ref ?Next@UnknownSchemeListIterator@@QAEPAV?$DynamicVectorClass@PAVColorScheme@@@@XZ=00603640
// @ref ?Unknown_00603C10@@YAHXZ=00603c10
// @ref ?Unknown_0049E5E0@DisplayClass@@QAEXXZ=0049e5e0
// @ref ?unknown_LightConvertClass_list_00832398@@3V?$DynamicVectorClass@PAVLightConvertClass@@@@A=00832398
// @ref ?ColorSchemes@@3V?$DynamicVectorClass@PAVColorScheme@@@@A=00ab6ef8

void __fastcall Set_Lighting_00520B00(int red, int green, int blue, bool unknown4)
{
    int index;
    for (index = 0; index < unknown_LightConvertClass_list_00832398.Count(); index++) {
        unknown_LightConvertClass_list_00832398[index]->Set_Tint(red, green, blue, unknown4);
    }
    for (index = 0; index < ColorSchemes.Count(); index++) {
        if (ColorSchemes[index]->unknown_0x310 > 1) {
            ((LightConvertClass *)ColorSchemes[index]->Converter)->Set_Tint(red, green, blue, unknown4);
        }
    }
    Set_Scheme_Lighting_00520A80(red, green, blue, unknown4);
    Map.Unknown_0049E5E0();
}
