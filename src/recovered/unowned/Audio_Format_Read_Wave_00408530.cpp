// int __fastcall Audio_Format_Read_Wave(FileClass *file, AudioFormat *format, int *data_size) -- 0x00408530
// Purpose: reads a RIFF WAVE header from the start of file: walks the
// chunks after the 'WAVE' tag, keeps the 'fmt ' chunk (at least a
// WAVEFORMATEX) and at the 'data' chunk stores its size and fills format
// (IMA ADPCM, tag 0x11: block size and 16-bit samples; PCM, tag 1: the
// sample width) from it. The file is left at the start of the data.
// Returns 1 for a supported format, else 0.
// @ref _malloc=00782630
// @ref _free=007825e8
#include "shared/raw_file_class.hpp"
#include "shared/crt_memory.hpp"
#include "shared/audio.hpp"

extern "C" void *__cdecl malloc(unsigned int size);
extern "C" void __cdecl free(void *block);

int __fastcall Audio_Format_Read_Wave(FileClass *file, AudioFormat *format, int *data_size)
{
    WAVEFORMATEX *wave = 0;
    int result = 0;
    if (data_size != 0) {
        *data_size = 0;
    }
    if (file != 0) {
        file->Seek(0, FILE_SEEK_START);
        struct {
            unsigned long Id;
            unsigned long Size;
            unsigned long Type;
        } riff;
        if (file->Read(&riff, sizeof(riff)) == sizeof(riff) && riff.Id == 'FFIR' && riff.Type == 'EVAW') {
            struct {
                unsigned long Id;
                unsigned long Size;
            } chunk;
            while (file->Read(&chunk, sizeof(chunk)) == sizeof(chunk)) {
                switch (chunk.Id) {
                case ' tmf':
                    if (chunk.Size < sizeof(WAVEFORMATEX)) {
                        wave = (WAVEFORMATEX *)malloc(sizeof(WAVEFORMATEX));
                        memset(wave, 0, sizeof(WAVEFORMATEX));
                    } else {
                        wave = (WAVEFORMATEX *)malloc(chunk.Size);
                        memset(wave, 0, chunk.Size);
                    }
                    file->Read(wave, chunk.Size);
                    wave->cbSize = (WORD)chunk.Size;
                    break;
                case 'atad':
                    *data_size = chunk.Size;
                    if (wave == 0) {
                        goto done;
                    }
                    if (wave->wFormatTag == 0x11) {
                        format->BlockSize = wave->nBlockAlign;
                        format->Type = AUDIO_FORMAT_IMA_ADPCM;
                        format->BytesPerSample = 2;
                    } else if (wave->wFormatTag == WAVE_FORMAT_PCM) {
                        format->Type = AUDIO_FORMAT_PCM;
                        format->BytesPerSample = wave->wBitsPerSample >> 3;
                    } else {
                        goto done;
                    }
                    format->Channels = wave->nChannels;
                    format->BytesPerSecond = wave->nAvgBytesPerSec;
                    format->Rate = wave->nSamplesPerSec;
                    format->unknown_00 = 4;
                    format->Update_Rate();
                    result = 1;
                    goto done;
                default:
                    file->Seek(chunk.Size, FILE_SEEK_CURRENT);
                    break;
                }
            }
        }
    }
done:
    if (wave != 0) {
        free(wave);
    }
    return result;
}
