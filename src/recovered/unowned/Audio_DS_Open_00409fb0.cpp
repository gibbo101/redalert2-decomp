// HRESULT __fastcall Audio_DS_Open(AudioDevice *device) -- 0x00409FB0
// Purpose: opens DirectSound output for a device: resets its mixer timing
// (33 ms passes), hands it to the mixing thread, creates the primary buffer
// in the device's default format (reported when the format is refused),
// reads the DirectSound caps and starts the primary buffer looping. Returns
// 0, or 0x80040000 when the primary buffer cannot be created.
// @ref ?Audio_Thread@@3UAudioThreadBlock@@A=00831560
// @ref ?Audio_DirectSound@@3PAUIDirectSound@@A=008315ac
// @ref ?Audio_Primary_Buffer@@3PAUIDirectSoundBuffer@@A=008315b0
// @ref ??_C@_0CK@KNMJ@Unable?5to?5set?5the?5desired?5primar@=007cd244
#include "shared/crt_string.hpp"
#include "shared/audio.hpp"
#include "shared/debug_printf.hpp"

HRESULT __fastcall Audio_DS_Open(AudioDevice *device)
{
    device->unknown_f4 = 100;
    device->Span.Set(33);
    device->Span.Set_08(1056);
    device->Span.Set_20(3168);
    Audio_Thread.Device = device;
    AudioFormat *format = &device->DefaultFormat;
    WAVEFORMATEX wave;
    memset(&wave, 0, sizeof(wave));
    wave.wFormatTag = WAVE_FORMAT_PCM;
    wave.nChannels = (WORD)format->Channels;
    wave.nSamplesPerSec = format->Rate;
    wave.nBlockAlign = (WORD)(format->BytesPerSample * format->Channels);
    wave.nAvgBytesPerSec = wave.nBlockAlign * wave.nSamplesPerSec;
    wave.wBitsPerSample = (WORD)(format->BytesPerSample * 8);
    wave.cbSize = 0;
    DSBUFFERDESC desc;
    memset(&desc, 0, sizeof(desc));
    desc.dwSize = sizeof(desc);
    desc.dwFlags = DSBCAPS_PRIMARYBUFFER;
    desc.dwBufferBytes = 0;
    if (Audio_DirectSound->CreateSoundBuffer(&desc, &Audio_Primary_Buffer, 0) != DS_OK) {
        Audio_Primary_Buffer = 0;
        return 0x80040000;
    }
    if (Audio_Primary_Buffer->SetFormat(&wave) != DS_OK) {
        Debug_Printf("Unable to set the desired primary format\n");
    }
    DSCAPS caps = { 0 };
    caps.dwSize = sizeof(caps);
    Audio_DirectSound->GetCaps(&caps);
    Audio_Primary_Buffer->Play(0, 0, DSBPLAY_LOOPING);
    device->unknown_1d8 = 4;
    device->unknown_1dc = 8;
    device->unknown_1e0 = 0;
    return 0;
}
