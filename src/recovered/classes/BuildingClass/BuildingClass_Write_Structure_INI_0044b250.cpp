// Building4D4 light: actual432FC0constructor result stored43E030; existingAbstract*field kept, realderivedcast explicit.
#include "shared/building.hpp"
#include "shared/house.hpp"
#include "shared/ini_class.hpp"
#include "shared/building_light.hpp"
extern "C" char const *unknown_structure_section_0079cb88;
extern "C" char const unknown_none_007ce9b4[];
extern "C" char const unknown_integer_format_007ce9bc[];
extern "C" char const unknown_append_integer_007cfa6c[];
extern "C" char const unknown_append_string_007cfa70[];
extern "C" char const unknown_structure_format_007cfa74[];
// @ref _unknown_structure_section_0079cb88=0079cb88
// @ref _unknown_none_007ce9b4=007ce9b4
// @ref _unknown_integer_format_007ce9bc=007ce9bc
// @ref _unknown_append_integer_007cfa6c=007cfa6c
// @ref _unknown_append_string_007cfa70=007cfa70
// @ref _unknown_structure_format_007cfa74=007cfa74
// @ref _sprintf=007820f4
void BuildingClass::Write_Structure_INI_0044b250(INIClass &ini)
{
    char key[12];
    char value[128];
    sprintf(key,unknown_integer_format_007ce9bc,Fetch_ID());
    int behavior=unknown_4d4?static_cast<BuildingLightClass *>(unknown_4d4)->Behavior:0;
    char const *tag=(unknown_34 && unknown_34->Class)?(char const *)unknown_34->Class->ID:unknown_none_007ce9b4;
    sprintf(value,unknown_structure_format_007cfa74,(char const *)House->IniName,(char const *)Type->ID,
            (int)(Health_Ratio()*256.0+0.5),unknown_slot104().X,unknown_slot104().Y,
            Dir_To_256(unknown_2e0.Current()),tag,(int)unknown_5ac,(int)unknown_59a,(int)unknown_530,
            (int)(signed char)unknown_5c6,behavior);
    TechnoTypeClass **upgrade=unknown_4c0;
    int remaining=3;
    do {
        char const *name=*upgrade?(char const *)(*upgrade)->ID:unknown_none_007ce9b4;
        sprintf(value+strlen(value),unknown_append_string_007cfa70,name);
        ++upgrade;
    }while(--remaining);
    sprintf(value+strlen(value),unknown_append_integer_007cfa6c,unknown_59b!=0);
    sprintf(value+strlen(value),unknown_append_integer_007cfa6c,unknown_599!=0);
    ini.Put_String(unknown_structure_section_0079cb88,key,value);
}
