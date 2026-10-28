// bool __fastcall Read_Scenario_0065e760(char const *name, bool fresh) (0x0065E760)
// Reads the named scenario file (Westwood's Read_Scenario): makes the
// required disk available, resets the frame counter, loads the file into an
// INI, records the name as the scenario's file name and reads it with
// Read_Scenario_INI (unofficial); false when the disk or the file fails.
// @ref ??_C@_0CE@JEJN@Read_Scenario_INI?5?9?5Filename?5is?5@=007f210c
// @ref ??_C@_0BL@IINH@Scenario?5ini?5load?5failed?$CB?6?$AA@=007f20f0
#include "shared/id_source.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/cd.hpp"
#include "shared/ccini_class.hpp"
#include "shared/cc_file_class.hpp"
#include "shared/cd_timer.hpp"
#include "shared/debug_printf.hpp"
#include "shared/crt_string.hpp"

bool __fastcall Read_Scenario_0065e760(char const *name, bool fresh)
{
    if (!CD().Force_Available(CD::RequiredCD)) {
        return false;
    }
    Frame = 0;
    CCINIClass ini;
    CCFileClass file(name);
    Debug_Printf("Read_Scenario_INI - Filename is %s\n", name);
    if (!ini.Load(file, true, false)) {
        Debug_Printf("Scenario ini load failed!\n");
        return false;
    }
    strcpy(unknown_id_source_a3d290->FileName, name);
    bool result = Read_Scenario_INI(ini, false);
    return result;
}
