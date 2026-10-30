#include "shared/wol_sink.hpp"
#include "shared/lobby.hpp"
#include "shared/string_table.hpp"
extern int wol_player_pings_b292ac[8];
extern wchar_t wol_ping_tooltip_b28de4[];
extern char wol_source_file_007fd62c[];
// @ref ?wol_player_pings_b292ac@@3PAHA=00b292ac
// @ref ?wol_ping_tooltip_b28de4@@3PAGA=00b28de4
// @ref ?wol_source_file_007fd62c@@3PADA=007fd62c
extern char wol_label_unknown_ping[];
// @ref ?wol_label_unknown_ping@@3PADA=007fd840
extern char wol_label_unknown[];
// @ref ?wol_label_unknown@@3PADA=007fec04
extern char wol_label_no_ping_tooltip[];
// @ref ?wol_label_no_ping_tooltip@@3PADA=007febe4
extern char wol_label_good[];
// @ref ?wol_label_good@@3PADA=007febd8
extern char wol_label_fair[];
// @ref ?wol_label_fair@@3PADA=007febcc
extern char wol_label_poor[];
// @ref ?wol_label_poor@@3PADA=007febc0
extern char wol_label_ping_tooltip[];
// @ref ?wol_label_ping_tooltip@@3PADA=007feba0
wchar_t *__fastcall Unknown_0074a4e0(wchar_t const *name)
{
    int ping=wol_player_pings_b292ac[Find_Slot_By_Name_005c8c30(name)];
    if(ping<0) {
        swprintf(wol_ping_tooltip_b28de4,StringTable::Load_String(wol_label_no_ping_tooltip,0,wol_source_file_007fd62c,0x36ef),name,StringTable::Load_String(wol_label_unknown,0,wol_source_file_007fd62c,0x36ef),StringTable::Load_String(wol_label_unknown_ping,0,wol_source_file_007fd62c,0x36ef));
    }
    else if(ping<300) {
        swprintf(wol_ping_tooltip_b28de4,StringTable::Load_String(wol_label_ping_tooltip,0,wol_source_file_007fd62c,0x36f1),name,StringTable::Load_String(wol_label_good,0,wol_source_file_007fd62c,0x36f1),ping);
    }
    else if(ping<500) {
        swprintf(wol_ping_tooltip_b28de4,StringTable::Load_String(wol_label_ping_tooltip,0,wol_source_file_007fd62c,0x36f3),name,StringTable::Load_String(wol_label_fair,0,wol_source_file_007fd62c,0x36f3),ping);
    }
    else {
        swprintf(wol_ping_tooltip_b28de4,StringTable::Load_String(wol_label_ping_tooltip,0,wol_source_file_007fd62c,0x36f5),name,StringTable::Load_String(wol_label_poor,0,wol_source_file_007fd62c,0x36f5),ping);
    }
    return wol_ping_tooltip_b28de4;
}
