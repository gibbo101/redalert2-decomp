// DirectSound declarations (as in the DirectX SDK's dsound.h and the
// Win32 mmsystem.h) used by the audio driver (0x00409390-0x0040AB80).
//
// The interfaces list every method in vtable order so that calls index the
// right slots. DirectSoundCreate is DSOUND.dll ordinal 1, imported without
// __declspec(dllimport): the game calls it through the jump thunk
// 0x00781BDE (IAT 0x0079A050).
#ifndef RA2_SHARED_DSOUND_API_HPP
#define RA2_SHARED_DSOUND_API_HPP

#include "shared/com_api.hpp"
#include "shared/win32_api.hpp"

#pragma pack(push, 1)
struct WAVEFORMATEX {
    WORD wFormatTag;
    WORD nChannels;
    DWORD nSamplesPerSec;
    DWORD nAvgBytesPerSec;
    WORD nBlockAlign;
    WORD wBitsPerSample;
    WORD cbSize;
};
#pragma pack(pop)

#define WAVE_FORMAT_PCM 1

struct DSBUFFERDESC {
    DWORD dwSize;
    DWORD dwFlags;
    DWORD dwBufferBytes;
    DWORD dwReserved;
    WAVEFORMATEX *lpwfxFormat;
};

struct DSCAPS {
    DWORD dwSize;
    DWORD dwFlags;
    DWORD dwMinSecondarySampleRate;
    DWORD dwMaxSecondarySampleRate;
    DWORD dwPrimaryBuffers;
    DWORD dwMaxHwMixingAllBuffers;
    DWORD dwMaxHwMixingStaticBuffers;
    DWORD dwMaxHwMixingStreamingBuffers;
    DWORD dwFreeHwMixingAllBuffers;
    DWORD dwFreeHwMixingStaticBuffers;
    DWORD dwFreeHwMixingStreamingBuffers;
    DWORD dwMaxHw3DAllBuffers;
    DWORD dwMaxHw3DStaticBuffers;
    DWORD dwMaxHw3DStreamingBuffers;
    DWORD dwFreeHw3DAllBuffers;
    DWORD dwFreeHw3DStaticBuffers;
    DWORD dwFreeHw3DStreamingBuffers;
    DWORD dwTotalHwMemBytes;
    DWORD dwFreeHwMemBytes;
    DWORD dwMaxContigFreeHwMemBytes;
    DWORD dwUnlockTransferRateHwBuffers;
    DWORD dwPlayCpuOverheadSwBuffers;
    DWORD dwReserved1;
    DWORD dwReserved2;
};

struct DSBCAPS {
    DWORD dwSize;
    DWORD dwFlags;
    DWORD dwBufferBytes;
    DWORD dwUnlockTransferRate;
    DWORD dwPlayCpuOverhead;
};

#define DS_OK 0
#define DSSCL_PRIORITY 2
#define DSBCAPS_PRIMARYBUFFER 0x01
#define DSBCAPS_LOCSOFTWARE 0x08
#define DSBCAPS_CTRLFREQUENCY 0x20
#define DSBCAPS_CTRLPAN 0x40
#define DSBCAPS_CTRLVOLUME 0x80
#define DSBPLAY_LOOPING 0x01
#define DSBSTATUS_PLAYING 0x01
#define DSBSTATUS_BUFFERLOST 0x02
#define DSBLOCK_FROMWRITECURSOR 0x01

struct IDirectSound;

struct __declspec(novtable) IDirectSoundBuffer : IUnknown {
    virtual HRESULT __stdcall GetCaps(DSBCAPS *caps) = 0;
    virtual HRESULT __stdcall GetCurrentPosition(DWORD *play, DWORD *write) = 0;
    virtual HRESULT __stdcall GetFormat(WAVEFORMATEX *format, DWORD size, DWORD *written) = 0;
    virtual HRESULT __stdcall GetVolume(LONG *volume) = 0;
    virtual HRESULT __stdcall GetPan(LONG *pan) = 0;
    virtual HRESULT __stdcall GetFrequency(DWORD *frequency) = 0;
    virtual HRESULT __stdcall GetStatus(DWORD *status) = 0;
    virtual HRESULT __stdcall Initialize(IDirectSound *sound, DSBUFFERDESC const *desc) = 0;
    virtual HRESULT __stdcall Lock(DWORD offset, DWORD bytes, void **audio1, DWORD *bytes1,
                                   void **audio2, DWORD *bytes2, DWORD flags) = 0;
    virtual HRESULT __stdcall Play(DWORD reserved, DWORD priority, DWORD flags) = 0;
    virtual HRESULT __stdcall SetCurrentPosition(DWORD position) = 0;
    virtual HRESULT __stdcall SetFormat(WAVEFORMATEX const *format) = 0;
    virtual HRESULT __stdcall SetVolume(LONG volume) = 0;
    virtual HRESULT __stdcall SetPan(LONG pan) = 0;
    virtual HRESULT __stdcall SetFrequency(DWORD frequency) = 0;
    virtual HRESULT __stdcall Stop() = 0;
    virtual HRESULT __stdcall Unlock(void *audio1, DWORD bytes1, void *audio2, DWORD bytes2) = 0;
    virtual HRESULT __stdcall Restore() = 0;
};

struct __declspec(novtable) IDirectSound : IUnknown {
    virtual HRESULT __stdcall CreateSoundBuffer(DSBUFFERDESC const *desc, IDirectSoundBuffer **buffer,
                                                IUnknown *outer) = 0;
    virtual HRESULT __stdcall GetCaps(DSCAPS *caps) = 0;
    virtual HRESULT __stdcall DuplicateSoundBuffer(IDirectSoundBuffer *original, IDirectSoundBuffer **duplicate) = 0;
    virtual HRESULT __stdcall SetCooperativeLevel(HWND window, DWORD level) = 0;
    virtual HRESULT __stdcall Compact() = 0;
    virtual HRESULT __stdcall GetSpeakerConfig(DWORD *config) = 0;
    virtual HRESULT __stdcall SetSpeakerConfig(DWORD config) = 0;
    virtual HRESULT __stdcall Initialize(GUID const *device) = 0;
};

extern "C" HRESULT __stdcall DirectSoundCreate(GUID const *device, IDirectSound **sound, IUnknown *outer);

#endif
