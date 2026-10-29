// bool __fastcall Save_Recording_Values(CCFileClass &file) -- 0x00516B00
// Writes the values a recording starts with (as Red Alert's Save_Recording_Values; the mirror of
// Load_Recording_Values 0x00516BA0): the house setting, two unnamed globals, the scenario's tech
// level and name, the special and the options. Select_Game 0x005135F0 inlines it.
#include "shared/cc_file_class.hpp"
#include "shared/id_source.hpp"
#include "shared/special.hpp"
#include "shared/options.hpp"
#include "shared/debug_printf.hpp"
#include "shared/unknown_globals.hpp"
// @ref ??_C@_0CL@JIBC@Saving?5recording?5values?5for?5scen@=007dbba0

bool __fastcall Save_Recording_Values(CCFileClass &file)
{
    Debug_Printf("Saving recording values for scenario : %s\n", unknown_id_source_a3d290->FileName);
    file.Write(&unknown_house_setting_7d88d8, sizeof(unknown_house_setting_7d88d8));
    file.Write(&unknown_a40d3c, sizeof(unknown_a40d3c));
    file.Write(&unknown_id_source_a3d290->TechLevel, sizeof(unknown_id_source_a3d290->TechLevel));
    file.Write(unknown_id_source_a3d290->FileName, sizeof(unknown_id_source_a3d290->FileName));
    file.Write(&unknown_a40c38, sizeof(unknown_a40c38));
    file.Write(&unknown_special_a40920, sizeof(unknown_special_a40920));
    file.Write(&Options, sizeof(Options));
    return true;
}
