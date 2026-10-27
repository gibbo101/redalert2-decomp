#include "shared/win32_api.hpp"
#include "shared/debug_printf.hpp"
extern "C" char const launch_check_log_007d5184[];
extern "C" char const launch_mutex_name_007d515c[];
// @ref _launch_check_log_007d5184=007d5184
// @ref _launch_mutex_name_007d515c=007d515c
// @ref __imp__CreateMutexA@12=0079a238
// @ref __imp__GetLastError@0=0079a1f4
// @ref __imp__CloseHandle@4=0079a1d4
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
bool __cdecl CopyProtection_Check_Already_Running_004918f0()
{
    Debug_Printf(launch_check_log_007d5184);
    HANDLE mutex=CreateMutexA(0,0,launch_mutex_name_007d515c);
    bool already_running=GetLastError()==183;
    if(mutex) CloseHandle(mutex);
    return already_running;
}
