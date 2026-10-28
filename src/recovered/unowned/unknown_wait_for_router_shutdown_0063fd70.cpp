// bool OwnerTalkClass::Wait_For_Router_Shutdown(unsigned long timeout, bool force) -- 0x0063FD70
// Purpose: waits up to timeout for the router process (+0x1C) to end; on a
// timeout either gives up (false) or, with force, terminates it (false and
// an error print when that fails). The handle is cleared once the process
// is gone; true when there was no process. Name from its debug text.
// Assumptions: callers 0x0053F810, 0x0053FB90, 0x0065CCC2, 0x0074F8C1;
// the error print's last argument is the failed result (0), as in the original.
#include "shared/win32_api.hpp"
#include "shared/debug_printf.hpp"
#include "shared/owner_talk.hpp"
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref __imp__WaitForMultipleObjects@16=0079a134
// @ref __imp__TerminateProcess@8=0079a258
// @ref __imp__GetLastError@0=0079a1f4
// @ref ??_C@_0BE@BALI@Router?5not?5running?6?$AA@=007eea68
// @ref ??_C@_0DA@EGFP@Wait_For_Router_Shutdown?5?9?5hRout@=007eeae8
// @ref ??_C@_0DB@PHEF@Failed?5to?5shut?5down?5router?5?9?5err@=007eea7c
// @ref ??_C@_0DH@BCOA@?$CK?$CK?$CKRouter?5process?5still?5running?5@=007eeab0

WIN32_IMPORT DWORD WINAPI WaitForMultipleObjects(DWORD count, HANDLE const *handles, BOOL all, DWORD timeout);
WIN32_IMPORT BOOL WINAPI TerminateProcess(HANDLE process, unsigned int code);

bool OwnerTalkClass::Wait_For_Router_Shutdown(unsigned long timeout, bool force)
{
    Debug_Printf("Wait_For_Router_Shutdown - hRouterProcess = %d\n", RouterProcess);
    if (RouterProcess != 0) {
        if (WaitForMultipleObjects(1, &RouterProcess, false, timeout) == 0x102) {
            if (!force) {
                return false;
            }
            Debug_Printf("***Router process still running - shutting it down***\n");
            BOOL result = TerminateProcess(RouterProcess, 0);
            if (!result) {
                Debug_Printf("Failed to shut down router - error code %d - %s\n", GetLastError(), result);
            } else {
                RouterProcess = 0;
            }
            return result != 0 ? true : false;
        }
        Debug_Printf("Router not running\n");
        RouterProcess = 0;
    }
    return true;
}
