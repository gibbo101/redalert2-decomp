// bool __fastcall Load_Recording_Values(CCFileClass &file) -- 0x00516BA0
// Reads the values a recording starts with (as Red Alert's
// Load_Recording_Values): the house setting, two unnamed globals, the
// scenario's tech level and name, the special and the options.
#include "shared/cc_file_class.hpp"
#include "shared/id_source.hpp"
#include "shared/special.hpp"
#include "shared/options.hpp"
#include "shared/debug_printf.hpp"
#include "shared/unknown_globals.hpp"
// @ref ?unknown_house_setting_7d88d8@@3HA=007d88d8
// @ref ?unknown_a40d3c@@3HA=00a40d3c
// @ref ?unknown_a40c38@@3HA=00a40c38
// @ref ?unknown_special_a40920@@3VSpecialClass@@A=00a40920
// @ref ?Options@@3VOptionsClass@@A=00a40b18
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ??_C@_0CL@JLID@Loaded?5recording?5values?5for?5scen@=007dbc64

bool __fastcall Load_Recording_Values(CCFileClass &file)
{
    file.Read(&unknown_house_setting_7d88d8, sizeof(unknown_house_setting_7d88d8));
    file.Read(&unknown_a40d3c, sizeof(unknown_a40d3c));
    file.Read(&unknown_id_source_a3d290->TechLevel, sizeof(unknown_id_source_a3d290->TechLevel));
    file.Read(unknown_id_source_a3d290->FileName, sizeof(unknown_id_source_a3d290->FileName));
    file.Read(&unknown_a40c38, sizeof(unknown_a40c38));
    file.Read(&unknown_special_a40920, sizeof(unknown_special_a40920));
    file.Read(&Options, sizeof(Options));
    Debug_Printf("Loaded recording values for scenario : %s\n", unknown_id_source_a3d290->FileName);
    return true;
}
