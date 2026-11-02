// long __cdecl Stream_Audio_Handler(VQAHandle *, long action, void *buffer, long nbytes) (0x004115A0): the player's
// VQAAUDIO_* dispatch (Close, Pause, Play and Stop expand inline).
#include "shared/ahandle.hpp"

long __cdecl Stream_Audio_Handler(VQAHandle *vqa, long action, void *buffer, long nbytes)
{
    VQAHandleP *vqap = (VQAHandleP *)vqa;
    VQAConfig *config;

    long error = AHANDLE_OK;

    switch (action) {
        case VQAAUDIO_INIT:
            config = &vqap->Config;
            config->TimerCallback = Simple_Timer_Callback_Audio_Handler;
            config->RefreshRate = 60;
            break;

        case VQAAUDIO_OPEN:
            error = Open_Audio_Handler((VQAHandleP *)vqa, (AhandleInitParams *)buffer, nbytes);
            break;

        case VQAAUDIO_CLOSE:
            error = Close_Audio_Handler((VQAHandleP *)vqa);
            break;

        case VQAAUDIO_START:
            error = Start_Audio_Handler((VQAHandleP *)vqa);
            break;

        case VQAAUDIO_LOAD:
            error = Load_Audio_Handler((VQAHandleP *)vqa, buffer, nbytes);
            break;

        case VQAAUDIO_PAUSE:
            error = Pause_Audio_Handler((VQAHandleP *)vqa);
            break;

        case VQAAUDIO_PLAY:
            error = Play_Audio_Handler((VQAHandleP *)vqa);
            break;

        case VQAAUDIO_STOP:
            error = Stop_Audio_Handler((VQAHandleP *)vqa);
            break;
    }

    return error;
}
