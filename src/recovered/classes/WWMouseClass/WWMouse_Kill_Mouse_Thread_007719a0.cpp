// void __fastcall Kill_Mouse_Thread() (0x007719A0)
// Stops the mouse thread, waits for it and closes the thread and mutex
// handles. Name is a hypothesis (tail-called from 0x00691304).
#include "shared/wwmouse.hpp"
// @ref ?MouseThreadActive@@3HA=00b2af64
// @ref ?MouseThreadInfo@@3UMouseThreadInfoStruct@@A=00b2af30
// @ref ?MouseThread@@3PAXA=00b2af4c
// @ref ?MouseMutex@@3PAXA=00b2af60

void __fastcall Kill_Mouse_Thread()
{
    if (MouseThreadActive) {
        MouseThreadInfo.Quit = 1;
        while (!MouseThreadInfo.Done) {
            Sleep(0);
        }
        WaitForSingleObject(MouseThread, 5000);
        CloseHandle(MouseThread);
        MouseThreadActive = 0;
    }
    if (MouseMutex != 0) {
        CloseHandle(MouseMutex);
        MouseMutex = 0;
    }
}
