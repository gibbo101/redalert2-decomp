// Complete MapSeedClass constructor at00576F50, original140+4.
#include "shared/map_seed.hpp"
extern "C" wchar_t *__cdecl wcscpy(wchar_t *,wchar_t const *);
// @ref ??0LoadOptionsClass@@=0053b0e0
// @ref ??1LoadOptionsClass@@=0053b130
// @ref ??_7MapSeedClass@@=007a5e24
// @ref ??_GMapSeedClass@@=0058da50
// @ref ?Load@MapSeedClass@@=005791c0
// @ref ?Save@MapSeedClass@@=00578f00
// @ref ?Validate@MapSeedClass@@=005794d0
// @ref ?Read_File_Description@MapSeedClass@@=005794e0
// @ref ?unknown_slot5@MapSeedClass@@=005796f0
// @ref ?unknown_slot6@MapSeedClass@@=00579710
// @ref ?unknown_slot7@MapSeedClass@@=00579730
// @ref ?unknown_slot8@MapSeedClass@@=00579750
// @ref ?Is_Loaded_006fa030@StringTable@@=006fa030
// @ref ?Load_String@StringTable@@=006f9ec0
// @ref _wcscpy=00783689
// @ref ??_C@_03LLMC@SED?$AA@=007e150c
// @ref ??_C@_0BC@CGOO@D?3?2Ra2?2MapGen?4cpp?$AA@=007e14f8
// @ref ??_C@_0BL@DEKD@TXT_RANDOM_MAP_DESCRIPTION?$AA@=007e14dc
MapSeedClass::MapSeedClass()
    : Theater(0),MapType(1),Resources(1),Ruggedness(0),Time(1),WaterAmount(0),
      NumPlayers(2),Tiberium(0),TiberiumLayout(0),Vegetation(0),UrbanPresence(0),
      Width(0),Height(0),Accessibility(0),RegionSize(0),Seed(-1)
{
    Extension="SED";
    DescriptionBuffer[0]=0;
    Description=DescriptionBuffer;
    if(StringTable::Is_Loaded_006fa030())
        wcscpy(DescriptionBuffer,StringTable::Load_String("TXT_RANDOM_MAP_DESCRIPTION",0,"D:\\Ra2\\MapGen.cpp",0xED1));
}
