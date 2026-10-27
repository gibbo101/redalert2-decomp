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
// @ref ??_C@_0BL@DEKD@TXT_RANDOM_MAP_DESCRIPTION?$AA@=007e14dc
// @ref ??_C@_0BC@CGOO@D?3?2Ra2?2MapGen?4cpp?$AA@=007e14f8
// @ref ??_C@_0BI@DPAE@Loading?5random?5map?3?5?$CFs?6?$AA@=007e16c4
#include "shared/map_seed.hpp"
#include "shared/cc_file_class.hpp"
#include "shared/ini_class.hpp"
#include "shared/debug_printf.hpp"
extern "C" wchar_t *__cdecl wcscpy(wchar_t *,wchar_t const *);
// @ref _wcscpy=00783689
// @ref ?Load_String@StringTable@@=006f9ec0
bool MapSeedClass::Load(char const *filename)
{
    if(filename) {
        Debug_Printf("Loading random map: %s\n",filename);
        CCFileClass file(filename);
        INIClass ini;
        if(ini.Load(file,false)) {
            wchar_t *description=DescriptionBuffer;
            ini.Get_Unicode("RandomMap","Description",StringTable::Load_String("TXT_RANDOM_MAP_DESCRIPTION",0,"D:\\Ra2\\MapGen.cpp",0x149B),description,128);
            Width=ini.Get_Int("RandomMap","Width",Width);
            Height=ini.Get_Int("RandomMap","Height",Height);
            NumPlayers=ini.Get_Int("RandomMap","NumPlayers",NumPlayers);
            Seed=ini.Get_Int("RandomMap","Seed",Seed);
            MapType=ini.Get_Int("RandomMap","MapType",MapType);
            Theater=ini.Get_Int("RandomMap","Theater",Theater);
            Time=ini.Get_Int("RandomMap","Time",Time);
            RegionSize=ini.Get_Int("RandomMap","RegionSize",RegionSize);
            Ruggedness=ini.Get_Int("RandomMap","Ruggedness",Ruggedness);
            Accessibility=ini.Get_Int("RandomMap","Accessibility",Accessibility);
            WaterAmount=ini.Get_Int("RandomMap","WaterAmount",WaterAmount);
            Tiberium=ini.Get_Int("RandomMap","Tiberium",Tiberium);
            TiberiumLayout=ini.Get_Int("RandomMap","TiberiumLayout",TiberiumLayout);
            Vegetation=ini.Get_Int("RandomMap","Vegetation",Vegetation);
            UrbanPresence=ini.Get_Int("RandomMap","UrbanPresence",UrbanPresence);
            Resources=ini.Get_Int("RandomMap","Resources",Resources);
            return true;
        }
    }
    return false;
}
