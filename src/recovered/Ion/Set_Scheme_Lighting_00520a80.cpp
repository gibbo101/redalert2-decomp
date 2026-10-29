// 0x00520A80: tints the converter of every scheme in the colour-scheme lists
// (0x00A76414) to red, green, blue.
#include "shared/lightning_storm.hpp"
#include "shared/color_scheme.hpp"
#include "shared/light_convert.hpp"
// @ref ?Next@UnknownSchemeListIterator@@QAEPAV?$DynamicVectorClass@PAVColorScheme@@@@XZ=00603640
// @ref ?Unknown_00603C10@@YAHXZ=00603c10

void __fastcall Set_Scheme_Lighting_00520A80(int red, int green, int blue, bool unknown4)
{
    UnknownSchemeListIterator iterator;
    for (DynamicVectorClass<ColorScheme *> *list = iterator.Next(); list != 0; list = iterator.Next()) {
        int count = Unknown_00603C10();
        for (int index = 0; index < count; index++) {
            ((LightConvertClass *)(*list)[index]->Converter)->Set_Tint(red, green, blue, unknown4);
        }
    }
}
