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

void __fastcall Receive_Launcher_Message_004919b0(MSG const *message)
{
    if(message->message==0xbeef) {
        Debug_Printf(launcher_received_log_007d5274);
        launcher_message_00851b3c=(char const *)MapViewOfFileEx((HANDLE)message->lParam,0xf001f,0,0,0,0);
        if(!launcher_message_00851b3c) {
            Debug_Printf(launcher_map_failed_log_007d5254);
            return;
        }
        Debug_Printf(launcher_message_log_007d523c,launcher_message_00851b3c);
    }
}
