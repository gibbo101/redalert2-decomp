// @ref ?Get_Unicode@INIClass@@=0050edf0
// @ref ?Put_Unicode@INIClass@@=0050ecf0
// @ref ??_C@_09ENKN@Resources?$AA@=007e1614
// @ref ??_C@_0O@IDIL@UrbanPresence?$AA@=007e1620
// @ref ??_C@_0L@JIMG@Vegetation?$AA@=007e1630
// @ref ??_C@_0P@NPBI@TiberiumLayout?$AA@=007e163c
// @ref ??_C@_08EAIC@Tiberium?$AA@=007cdcd0
// @ref ??_C@_0M@HF@WaterAmount?$AA@=007e164c
// @ref ??_C@_0O@DOPL@Accessibility?$AA@=007e1658
// @ref ??_C@_0L@KENK@Ruggedness?$AA@=007e1668
// @ref ??_C@_0L@JMFD@RegionSize?$AA@=007e1674
// @ref ??_C@_04OAHI@Time?$AA@=007d4f6c
// @ref ??_C@_07OHHF@Theater?$AA@=007cf004
// @ref ??_C@_07FBOP@MapType?$AA@=007e1680
// @ref ??_C@_04NNOK@Seed?$AA@=007e1688
// @ref ??_C@_0L@JLOO@NumPlayers?$AA@=007e1690
// @ref ??_C@_06FOPC@Height?$AA@=007d0bf0
// @ref ??_C@_05PJLH@Width?$AA@=007e169c
// @ref ??_C@_09CKPM@RandomMap?$AA@=007e15dc
// @ref ??_C@_0M@DKEL@Description?$AA@=007d1444
// @ref ??_C@_0BN@ELGP@Saving?5random?5map?3?5?$CFs?5?9?5?$CFls?6?$AA@=007e16a4
#include "shared/map_seed.hpp"
#include "shared/cc_file_class.hpp"
#include "shared/ini_class.hpp"
#include "shared/debug_printf.hpp"
extern "C" wchar_t *__cdecl wcscpy(wchar_t *,wchar_t const *);
// @ref _wcscpy=00783689
// @ref ?Load_String@StringTable@@=006f9ec0
bool MapSeedClass::Save(char const *filename,wchar_t const *description)
{
    if(filename) {
        Debug_Printf("Saving random map: %s - %ls\n",filename,description);
        CCFileClass file(filename);
        INIClass ini;
        if(description) wcscpy(DescriptionBuffer,description);
        ini.Put_Unicode("RandomMap","Description",description);
        ini.Put_Int("RandomMap","Width",Width);
        ini.Put_Int("RandomMap","Height",Height);
        ini.Put_Int("RandomMap","NumPlayers",NumPlayers);
        ini.Put_Int("RandomMap","Seed",Seed);
        ini.Put_Int("RandomMap","MapType",MapType);
        ini.Put_Int("RandomMap","Theater",Theater);
        ini.Put_Int("RandomMap","Time",Time);
        ini.Put_Int("RandomMap","RegionSize",RegionSize);
        ini.Put_Int("RandomMap","Ruggedness",Ruggedness);
        ini.Put_Int("RandomMap","Accessibility",Accessibility);
        ini.Put_Int("RandomMap","WaterAmount",WaterAmount);
        ini.Put_Int("RandomMap","Tiberium",Tiberium);
        ini.Put_Int("RandomMap","TiberiumLayout",TiberiumLayout);
        ini.Put_Int("RandomMap","Vegetation",Vegetation);
        ini.Put_Int("RandomMap","UrbanPresence",UrbanPresence);
        ini.Put_Int("RandomMap","Resources",Resources);
        ini.Save(file);
        return true;
    }
    return false;
}
