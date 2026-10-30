#include "shared/map_select.hpp"
#include "shared/ww_message_box.hpp"
#include "shared/string_table.hpp"
extern char const unknown_mapselect_file_7e1bd4[];
extern char const unknown_mapselect_failure_7e1bc0[];
extern char const unknown_txt_ok_7db8f4[];
extern unsigned short const unknown_blank_caption_7d64f4[];
// @ref ?Advance_Progression_0058f720@MapSelect@@=0058f720
// @ref ??0Wstring@@QAE@PBD@Z=0076d920
char const *__fastcall Map_Select_Advance_0058f620(UnknownIDSource *scenario,char const *name)
{
    if(!MapSelect().Advance_Progression_0058f720(scenario,name)) {
        WWMessageBox(unknown_blank_caption_7d64f4).Process(
            StringTable::Load_String(unknown_mapselect_failure_7e1bc0,0,unknown_mapselect_file_7e1bd4,152),
            StringTable::Load_String(unknown_txt_ok_7db8f4,0,unknown_mapselect_file_7e1bd4,152),0,0,false);
        return 0;
    }
    return name;
}
