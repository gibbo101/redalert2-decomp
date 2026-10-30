#include "shared/map_select.hpp"
#include "shared/id_source.hpp"
#include "shared/ww_message_box.hpp"
#include "shared/string_table.hpp"
#include "shared/debug_printf.hpp"
extern "C" unsigned int __cdecl strlen(char const *);
extern char const unknown_mapselect_file_7e1bd4[];
extern char const unknown_mapselect_failure_7e1bc0[];
extern char const unknown_txt_ok_7db8f4[];
extern unsigned short const unknown_blank_caption_7d64f4[];
extern char const unknown_mapselect_format_7e1b98[];
// @ref ?unknown_mapselect_file_7e1bd4@@=007e1bd4
// @ref ?unknown_mapselect_failure_7e1bc0@@=007e1bc0
// @ref ?unknown_txt_ok_7db8f4@@=007db8f4
// @ref ?unknown_blank_caption_7d64f4@@=007d64f4
// @ref ?unknown_mapselect_format_7e1b98@@=007e1b98
// @ref ??0MSEngine@@=005b2be0
// @ref ??1MSEngine@@=005b2c70
// @ref ??0MapSelectData@@=005aff10
// @ref ??1MapSelectData@@=005affa0
// @ref ??0Wstring@@QAE@XZ=0076d910
// @ref ??1Wstring@@=0076d9e0
// @ref ??BSystemTimerClass@@=0069a430
// @ref ?Presentation_0058f900@MapSelect@@=0058f900
// @ref ??_7MapSelect@@6B@=007a608c
// @ref ?Unknown_Slot1@MSEngine@@=0058fd90
// @ref ?Unknown_Slot2@MapSelect@@=0058fcc0
// @ref ??_GMapSelect@@=0058fda0
// @ref ?Load_String@StringTable@@=006f9ec0
// @ref ?Process@WWMessageBox@@=005b46b0
// @ref ?Debug_Printf@@=004068f0
// @ref ??3@YAXPAX@Z=00781d3b
char const *__fastcall Map_Selection_0058f510(UnknownIDSource *scenario)
{
    if(!MapSelect().Presentation_0058f900(scenario)) {
        WWMessageBox(unknown_blank_caption_7d64f4).Process(
            StringTable::Load_String(unknown_mapselect_failure_7e1bc0,0,unknown_mapselect_file_7e1bd4,134),
            StringTable::Load_String(unknown_txt_ok_7db8f4,0,unknown_mapselect_file_7e1bd4,134),0,0,false);
        return 0;
    }
    Debug_Printf(unknown_mapselect_format_7e1b98,scenario->FileName,scenario->unknown_2304);
    return strlen(scenario->FileName)==0?0:scenario->FileName;
}
