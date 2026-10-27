// void Start_Mouse_Thread() (0x007717E0)
// Creates the mouse mutex and the time-critical mouse thread (16 ms period);
// when the priority cannot be raised it reports the error and waits for the
// thread to finish. Name is a hypothesis (called from 0x0069003F).
#include "shared/wwmouse.hpp"
// @ref ?MouseMutex@@3PAXA=00b2af60
// @ref ?MouseThreadActive@@3HA=00b2af64
// @ref ?MouseThreadInfo@@3UMouseThreadInfoStruct@@A=00b2af30
// @ref ?MouseThread@@3PAXA=00b2af4c
// @ref ?MouseThreadID@@3KA=00b2af50
// @ref ?Mouse_Thread@@YGKPAX@Z=00771900
// @ref ??_C@_0DI@MILH@Unable?5to?5change?5the?5priority?5of@=008012e0
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0

void Start_Mouse_Thread()
{
    char buffer[1024];

    if (MouseMutex == 0) {
        MouseMutex = CreateMutexA(0, 0, 0);
    }
    if (!MouseThreadActive && MouseMutex != 0) {
        MouseThreadInfo.Quit = 0;
        MouseThreadInfo.Done = 0;
        MouseThreadInfo.Started = 0;
        MouseThreadInfo.Delay = 16;
        MouseThreadInfo.Count = 0;
        MouseThread = CreateThread(0, 0x1000, Mouse_Thread, &MouseThreadInfo, 0, &MouseThreadID);
        if (MouseThread != 0) {
            MouseThreadActive = 1;
            if (!SetThreadPriority(MouseThread, THREAD_PRIORITY_TIME_CRITICAL)) {
                FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM, 0, GetLastError(), 0, buffer, sizeof(buffer), 0);
                Debug_Printf("Unable to change the priority of the mouse thread - %s\n", buffer);
                while (!MouseThreadInfo.Done) {
                    Sleep(0);
                }
                WaitForSingleObject(MouseThread, 5000);
                CloseHandle(MouseThread);
                MouseThreadActive = 0;
            }
        }
    }
}
