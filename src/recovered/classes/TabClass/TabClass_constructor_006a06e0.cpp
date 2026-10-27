// TabClass::TabClass() (0x006A06E0)
// The sidebar's constructor, the notice sink and the member timers; looks up
// the button slots of the bar's commands by name (0x006A0580, expanded here)
// and registers itself as the planning mode's notice sink.
#include "shared/tab.hpp"
#include "shared/crt_string.hpp"
// @ref ??_C@_0N@CNHO@PlanningMode?$AA@=007dcbc8
// @ref ??_C@_04DFLL@Stop?$AA@=007cd898
// @ref ??_C@_05ICEM@Guard?$AA@=007cd8dc
// @ref ??_C@_05NING@Cheer?$AA@=007db03c
// @ref ??_C@_06DBCK@Team01?$AA@=007f6848
// @ref ??_C@_06GEAE@Team03?$AA@=007f6838
// @ref ??_C@_06HDMK@Beacon?$AA@=007f6824
// @ref ??_C@_06KMDI@Deploy?$AA@=007db07c
// @ref ??_C@_06MOJD@Team02?$AA@=007f6840
// @ref ??_C@_0L@EACJ@AttackMove?$AA@=007f682c
// @ref ??_C@_0L@PODG@TypeSelect?$AA@=007dcc54
// @ref ??0SidebarClass@@QAE@XZ=0067b700
// @ref ??0UnknownTab4EEC@@QAE@XZ=00494510
// @ref ?Unknown_Set_Sink_00613e00@@YIXPAVINoticeSink@@@Z=00613e00
// @ref ??_ETabClass@@UAEPAXI@Z=0059ff90
// @ref ?AddRef@GScreenClass@@UAGKXZ=0040d100
// @ref ?Release@GScreenClass@@UAGKXZ=0040d110
// @ref ??_7INoticeSink@@6B@=0079ae44
// @ref ??_7TabClass@@6BSidebarClass@@@=007a64e4
// @ref ??_7TabClass@@6BINoticeSink@@@=007a64dc
// @ref ?Frame@@3HA=00a40d2c
// @ref ?unknown_command_names_7f67f8@@3PAPBDA=007f67f8
// @ref ?unknown_no_command_7f67f4@@3HA=007f67f4
// @ref ?unknown_int_abe464@@3HA=00abe464
// @ref ?unknown_int_abe294@@3HA=00abe294
// @ref ?unknown_int_abd910@@3HA=00abd910
// @ref ?unknown_int_abe278@@3HA=00abe278
// @ref ?unknown_int_abe2b8@@3HA=00abe2b8
// @ref ?unknown_int_abe36c@@3HA=00abe36c
// @ref ?unknown_int_abe2bc@@3HA=00abe2bc
// @ref ?unknown_int_abe370@@3HA=00abe370
// @ref ?unknown_int_abe378@@3HA=00abe378
// @ref ?unknown_int_abe468@@3HA=00abe468
// @ref ?unknown_int_abe290@@3HA=00abe290

TabClass::TabClass() : unknown_4f14(true), unknown_4f15(true), unknown_4f16(true)
{
    unknown_int_abe464 = Unknown_006A0580("AttackMove");
    unknown_int_abe294 = Unknown_006A0580("Beacon");
    unknown_int_abd910 = Unknown_006A0580("Cheer");
    unknown_int_abe278 = Unknown_006A0580("Deploy");
    unknown_int_abe2b8 = Unknown_006A0580("Guard");
    unknown_int_abe36c = Unknown_006A0580("PlanningMode");
    unknown_int_abe2bc = Unknown_006A0580("Stop");
    unknown_int_abe370 = Unknown_006A0580("Team01");
    unknown_int_abe378 = Unknown_006A0580("Team02");
    unknown_int_abe468 = Unknown_006A0580("Team03");
    unknown_int_abe290 = Unknown_006A0580("TypeSelect");
    Unknown_Set_Sink_00613e00(this);
}
