// DWORD __stdcall Audio_Thread_Proc(void *parameter) -- 0x004094D0
// Purpose: the DirectSound mixing thread. Until asked to quit, each pass
// (unless the device is busy, which waits 5 ms) ticks the device's mixer
// timing, refills every playing channel's buffer by the frames played since
// the last pass (stopping channels whose buffer stopped or ran out) and
// updates the global levels and the device; then it sleeps the interval.
// The level block is Audio_Run_With_Levels_Updated 0x0040A8C0 written out
// (the original keeps its device test; VC6 does not inline that function).
// @ref ?Audio_Device_First_Channel@@YIPAUAudioListNode@@PAUAudioDevice@@PAUAudioListIterator@@@Z=004035b0
// @ref ?Next@AudioListIterator@@QAEPAUAudioListNode@@XZ=004035d0
// @ref ?Tick@AudioTimeSpan@@QAEX_J@Z=00403920
// @ref ?Audio_Now@@YI_JXZ=004092d0
// @ref ?Audio_DS_Fill@@YIHPAUAudioChannelBuffer@@H@Z=004097a0
// @ref ?Audio_Lock@@3UCRITICAL_SECTION@@A=00831590
// @ref ?Audio_Global_Levels@@3PAPAUAudioLevelSet@@A=0083144c
// @ref ?Clear_Changed@AudioLevelSet@@QAEXXZ=00401170
// @ref ?Update@AudioLevelSet@@QAEXXZ=00401080
// @ref ?Run_Update@AudioDevice@@QAEXXZ=00403810
#include "shared/audio.hpp"

DWORD __stdcall Audio_Thread_Proc(void *parameter)
{
    AudioThreadBlock *block = (AudioThreadBlock *)parameter;
    block->Started = 1;
    block->Done = 0;
    while (block->Quit == 0) {
        if (block->Device != 0) {
            if (block->Device->unknown_busy_104 == 0) {
                AudioDevice *device = block->Device;
                EnterCriticalSection(&Audio_Lock);
                __int64 now = Audio_Now();
                device->Span.Tick(now);
                AudioListIterator cursor;
                for (AudioChannel *channel = (AudioChannel *)Audio_Device_First_Channel(device, &cursor); channel != 0;
                     channel = (AudioChannel *)cursor.Next()) {
                    if (channel->Flags & AUDIO_CHANNEL_PLAYING) {
                        if (Audio_DS_Channel_Is_Playing(channel)) {
                            channel->DriverBuffer->unknown_18 = now - channel->DriverBuffer->unknown_10;
                            channel->DriverBuffer->unknown_10 = now;
                            AudioChannelBuffer *record = channel->DriverBuffer;
                            DWORD play;
                            record->Buffer->GetCurrentPosition(&play, &record->WriteCursor);
                            unsigned int position = play / record->FrameBytes;
                            int frames = position - record->unknown_0c;
                            if (frames != 0) {
                                if (frames < 0) {
                                    frames = position - record->unknown_0c + 4;
                                }
                                if (frames > 0) {
                                    if ((unsigned int)(record->unknown_0c += frames) >= 4) {
                                        record->unknown_0c &= 3;
                                    }
                                    record->unknown_d4 += frames;
                                    frames *= record->FrameBytes;
                                    int filled = Audio_DS_Fill(record, frames);
                                    if (record->unknown_40 > frames) {
                                        record->unknown_40 = frames;
                                    }
                                    if ((record->unknown_08 -= frames) <= 0 || filled == 0) {
                                        record->Buffer->Stop();
                                    }
                                }
                            }
                            record->unknown_d0++;
                        } else {
                            if (channel->DriverBuffer->Buffer != 0) {
                                channel->DriverBuffer->Buffer->Stop();
                            }
                            if (channel->unknown_stop_callback_164 != 0) {
                                channel->unknown_stop_callback_164(channel);
                            }
                        }
                    }
                }
                if (device != 0) {
                    Audio_Global_Levels[2]->Update();
                    Audio_Global_Levels[3]->Update();
                    Audio_Global_Levels[1]->Update();
                    Audio_Global_Levels[0]->Update();
                    Audio_Global_Levels[6]->Update();
                    Audio_Global_Levels[7]->Update();
                    Audio_Global_Levels[5]->Update();
                    Audio_Global_Levels[4]->Update();
                    device->Run_Update();
                    Audio_Global_Levels[3]->Clear_Changed();
                    Audio_Global_Levels[2]->Clear_Changed();
                    Audio_Global_Levels[1]->Clear_Changed();
                    Audio_Global_Levels[0]->Clear_Changed();
                    Audio_Global_Levels[6]->Clear_Changed();
                    Audio_Global_Levels[7]->Clear_Changed();
                    Audio_Global_Levels[5]->Clear_Changed();
                    Audio_Global_Levels[4]->Clear_Changed();
                }
                LeaveCriticalSection(&Audio_Lock);
            } else {
                Sleep(5);
                goto next;
            }
        }
        Sleep((DWORD)block->Interval);
next:
        block->PassCount++;
    }
    block->Done = 1;
    return 0;
}
