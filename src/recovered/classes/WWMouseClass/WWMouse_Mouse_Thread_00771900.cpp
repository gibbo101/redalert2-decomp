// DWORD WINAPI Mouse_Thread(LPVOID parameter) (0x00771900)
// Thread procedure: until asked to quit, processes the mouse under the mutex
// and sleeps for the configured delay. Name is a hypothesis.
#include "shared/wwmouse.hpp"
// @ref ?_Mouse@@3PAVWWMouseClass@@A=00b2af5c
// @ref ?MouseMutex@@3PAXA=00b2af60
// @ref ?Process_Mouse@WWMouseClass@@QAEXXZ=00773400
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ??_C@_0EA@PAMP@Warning?3?5Probable?5deadlock?5occur@=00801318
// @ref ??_C@_0BC@JOPK@D?3?2Ra2?2wwmous?4cpp?$AA@=00801358

DWORD WINAPI Mouse_Thread(LPVOID parameter)
{
    MouseThreadInfoStruct *info = (MouseThreadInfoStruct *)parameter;
    info->Started = 1;
    info->Done = 0;
    while (!info->Quit) {
        Block_Mouse();
        if (_Mouse != 0) {
            _Mouse->Process_Mouse();
        }
        Unblock_Mouse();
        Sleep((DWORD)info->Delay);
        info->Count++;
    }
    info->Done = 1;
    return 0;
}
