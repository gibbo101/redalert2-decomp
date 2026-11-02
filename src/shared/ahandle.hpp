// The VQ movie audio handler (Westwood's AHANDLE.CPP as in Tiberian Sun; unit 0x00411420-0x00412385): plays a
// movie's HMI-sized audio blocks through a looping DirectSound secondary buffer fed by a 16 ms multimedia
// timer and gives the player its audio clock. One handle (0x00839D90). Only that unit includes this header.
#ifndef RA2_SHARED_AHANDLE_HPP
#define RA2_SHARED_AHANDLE_HPP

#include "shared/vqa_player.hpp"
#include "shared/dsound_api.hpp"
#include "shared/debug_printf.hpp"
#include "shared/sound_available.hpp"
#include "shared/crt_memory.hpp"

void *unknown_directsound_40a6c0();             // 0x0040A6C0 the DirectSound object
long __fastcall Audio_DS_Volume_Attenuation(int volume);    // 0x0040A820
extern float unknown_volume_a40b48;             // 0x00A40B48 movie volume scale
unsigned long unknown_ticks_004d0090();         // 0x004D0090 game ticks (1/60 s)

typedef void (__stdcall *LPTIMECALLBACK)(unsigned int timer, unsigned int message, DWORD user, DWORD unused1, DWORD unused2);
WIN32_IMPORT unsigned int WINAPI timeBeginPeriod(unsigned int period);
WIN32_IMPORT unsigned int WINAPI timeEndPeriod(unsigned int period);
WIN32_IMPORT unsigned int WINAPI timeSetEvent(unsigned int delay, unsigned int resolution, LPTIMECALLBACK callback,
    DWORD user, unsigned int flags);
WIN32_IMPORT unsigned int WINAPI timeKillEvent(unsigned int timer);
WIN32_IMPORT DWORD WINAPI GetCurrentThreadId();

// The audio handler's results (VQA library codes: the handler answers -1 when it succeeded).
enum {
    AHANDLE_OK = -1,
    AHANDLE_ERROR = -13
};
enum {
    VQAAUDIO_LOAD = 5,
    VQAAUDIO_PLAY = 8
};

struct AhandleInitParams {
    unsigned short SampleRate;
    unsigned char Channels;
    unsigned char BitsPerSample;
    unsigned long Flags;
    void *Callback1;
    void *Callback2;
};

#define AHANDLEF_IS_PAUSED (1 << 0)

struct Ahandle {
    enum {
        MAX_HANDLES = 1,
        MAX_BUFFERS = 2
    };

    bool Used;                              // +0x00
    unsigned int Volume;                    // +0x04
    unsigned short SampleRate;              // +0x08
    unsigned char Channels;                 // +0x0A
    unsigned char BitsPerSample;            // +0x0B
    char Reserved1[8];
    unsigned long LastPlaybackPosition;     // +0x14
    unsigned long LastTimerTick;            // +0x18
    unsigned long PauseAdjust;              // +0x1C
    unsigned long TickCount;                // +0x20
    unsigned long InitFlags;                // +0x24
    unsigned long Flags;                    // +0x28
    char Reserved2[20];
    int AudioBufReadIndex;                  // +0x40
    int AudioBufWriteIndex;                 // +0x44
    BOOL AudioBufInUse[MAX_BUFFERS];        // +0x48
    void *AudioBuf[MAX_BUFFERS];            // +0x50
    unsigned long AudioBufSize[MAX_BUFFERS];    // +0x58
    unsigned int TimerHandle;               // +0x60
    DSBUFFERDESC BufferDesc;                // +0x64
    WAVEFORMATEX DsBuffFormat;              // +0x78
    IDirectSoundBuffer *SecondaryBufferPtr; // +0x8C
    unsigned long SecondaryBufferSize;      // +0x90
    unsigned long ChunksMovedToAudioBuffer; // +0x94
    unsigned long LastChunkPosition;        // +0x98
    unsigned long EndLastAudioChunk;        // +0x9C
    CRITICAL_SECTION CriticalSection;       // +0xA0
    long SuspendAudioCallback;              // +0xB8
};

typedef long (__cdecl *AHANDLE_CALLBACK_1)(VQAHandle *vqa);
typedef long (__cdecl *AHANDLE_CALLBACK_2)(VQAHandle *vqa, void *buffer);

extern Ahandle _handles[Ahandle::MAX_HANDLES];          // 0x00839D90
extern AHANDLE_CALLBACK_1 _AHandleCallbackFunc1;        // 0x00839D84
extern AHANDLE_CALLBACK_2 _AHandleCallbackFunc2;        // 0x00839D88

long __cdecl Open_Audio_Handler(VQAHandleP *vqap, AhandleInitParams *params, long b);
long __cdecl Close_Audio_Handler(VQAHandleP *vqap);
long __cdecl Start_Audio_Handler(VQAHandleP *vqap);
long __cdecl Stop_Audio_Handler(VQAHandleP *vqap);
long __cdecl Play_Audio_Handler(VQAHandleP *vqap);
long __cdecl Pause_Audio_Handler(VQAHandleP *vqap);
long __cdecl Load_Audio_Handler(VQAHandleP *vqap, void *buffer, long nbytes);
void __stdcall AudioCallback(unsigned int uTimerID, unsigned int, DWORD dwUser, DWORD, DWORD);
unsigned long __cdecl Simple_Timer_Callback_Audio_Handler(VQAHandle *vqa);
void Pause_All_Audio_Handler();
void Resume_All_Audio_Handler();

#endif
