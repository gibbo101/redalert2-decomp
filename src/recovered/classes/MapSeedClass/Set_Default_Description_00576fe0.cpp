// Reset the inline description buffer to the localized default, original40+8.
#include "shared/map_seed.hpp"
extern "C" wchar_t *__cdecl wcscpy(wchar_t *,wchar_t const *);
// @ref ?Load_String@StringTable@@=006f9ec0
// @ref _wcscpy=00783689
// @ref ??_C@_0BC@CGOO@D?3?2Ra2?2MapGen?4cpp?$AA@=007e14f8
// @ref ??_C@_0BL@DEKD@TXT_RANDOM_MAP_DESCRIPTION?$AA@=007e14dc
void MapSeedClass::Set_Default_Description_00576fe0()
{
    wcscpy(DescriptionBuffer,StringTable::Load_String("TXT_RANDOM_MAP_DESCRIPTION",0,"D:\\Ra2\\MapGen.cpp",0xED1));
}
