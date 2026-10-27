#include "shared/launcher_validation.hpp"
#include "shared/crt_string.hpp"
extern char const launcher_validate_log_007d52ec[];
extern char const launcher_expected_message_007d52b8[];
bool __fastcall Probe_Launcher_Registry_00491b70();
// @ref ?launcher_validate_log_007d52ec@@=007d52ec
// @ref ?launcher_expected_message_007d52b8@@=007d52b8
// Zero-argument convention and bool spelling remain source/ABI hypotheses.
bool __fastcall Validate_Launcher_00491a10()
{
    Debug_Printf(launcher_validate_log_007d52ec);
    if (launcher_message_00851b3c)
        return strcmp(launcher_message_00851b3c,launcher_expected_message_007d52b8)==0;
    return Probe_Launcher_Registry_00491b70();
}
