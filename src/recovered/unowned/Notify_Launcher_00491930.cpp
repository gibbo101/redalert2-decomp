#include "shared/launcher_validation.hpp"
// @ref ?Debug_Printf@@=004068f0
// @ref ?launcher_message_00851b3c@@=00851b3c
// @ref ?launcher_notify_log_007d5218@@=007d5218
// @ref ?launcher_event_007d51f0@@=007d51f0
// @ref ?launcher_notified_log_007d51dc@@=007d51dc
// @ref ?launcher_notify_failed_log_007d51b8@@=007d51b8
// @ref ?launcher_received_log_007d5274@@=007d5274
// @ref ?launcher_map_failed_log_007d5254@@=007d5254
// @ref ?launcher_message_log_007d523c@@=007d523c
// @ref ?launcher_registry_key_007d52ac@@=007d52ac
// @ref ?launcher_registry_value_007d52a8@@=007d52a8
// @ref ?launcher_shutdown_log_007d530c@@=007d530c

bool __cdecl Notify_Launcher_00491930()
{
    Debug_Printf(launcher_notify_log_007d5218);
    MSG message;
    PeekMessageA(&message,0,0x400,0x400,0);
    HANDLE event=OpenEventA(2,1,launcher_event_007d51f0);
    if(event) {
        SetEvent(event);
        CloseHandle(event);
        Debug_Printf(launcher_notified_log_007d51dc);
        return true;
    }
    Debug_Printf(launcher_notify_failed_log_007d51b8);
    return false;
}
