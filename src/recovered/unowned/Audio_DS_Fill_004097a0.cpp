// int __fastcall Audio_DS_Fill(AudioChannelBuffer *record, int bytes) -- 0x004097A0
// Purpose: writes bytes of decoded sound into the channel's DirectSound
// buffer at the fill position (+0x30), wrapping at the end of the buffer.
// Each pass locks the free space (restoring a lost buffer up to three
// times), then fills it piece by piece: asks the channel for its next
// block and its end-of-source handling when the current piece (+0x28
// source pointer, +0x2C bytes left) runs out, writes silence (0 for 16-bit,
// 0x80 for 8-bit) when there is nothing left, and otherwise runs the
// decoder. Returns 1 when everything was written, 0 on a lock, restore,
// buffer-management or decoder failure (each but the last reported).
// @ref ?Audio_DS_Setup_Decoder@@YIXPAUAudioChannelBuffer@@@Z=00409b60
// @ref ?Audio_Now@@YA_JXZ=004092d0
// @ref ??_C@_0BB@OLEN@Restored?5buffer?6?$AA@=007cd230
// @ref ??_C@_0BH@FAOO@Failed?5to?5lock?5buffer?6?$AA@=007cd1fc
// @ref ??_C@_0BK@EALD@Failed?5to?5restore?5buffer?6?$AA@=007cd214
// @ref ??_C@_0CD@CFEI@Buffer?5management?5out?5by?5?$CFd?5byte@=007cd1d8
#include "shared/crt_memory.hpp"
#include "shared/audio.hpp"
#include "shared/debug_printf.hpp"


int __fastcall Audio_DS_Fill(AudioChannelBuffer *record, int bytes)
{
    void *audio1 = 0;
    void *audio2 = 0;
    DWORD bytes1 = 0;
    DWORD bytes2 = 0;
    int locked = 0;
    int result = 0;
    while (bytes > 0) {
        if (record->unknown_38 <= 0) {
            record->PlayCursor = 0;
            record->unknown_38 = record->BufferBytes;
        }
        int written = 0;
        int size = bytes;
        if ((DWORD)size > (DWORD)record->unknown_38) {
            size = record->unknown_38;
        }
        if (locked) {
            record->Buffer->Unlock(audio1, bytes1, audio2, bytes2);
            locked = 0;
        }
        DWORD offset = record->PlayCursor;
        int retries = 3;
        while (record->Buffer->Lock(offset, size, &audio1, &bytes1, &audio2, &bytes2, 0) != DS_OK) {
            if (record->Buffer->Restore() != DS_OK) {
                Debug_Printf("Failed to restore buffer\n");
                goto finish;
            }
            record->unknown_2c = 0;
            record->unknown_08 = 0;
            record->unknown_3c = record->FrameBytes * 4;
            record->Buffer->SetCurrentPosition(0);
            DWORD play;
            record->Buffer->GetCurrentPosition(&play, &record->WriteCursor);
            record->unknown_0c = play / record->FrameBytes;
            record->unknown_10 = Audio_Now();
            record->unknown_40 = record->BufferBytes;
            record->Buffer->GetCurrentPosition((DWORD *)&record->PlayCursor, &record->WriteCursor);
            record->unknown_38 = record->BufferBytes - record->PlayCursor;
            record->unknown_d0 = 0;
            record->unknown_d8 = record->unknown_0c;
            record->unknown_d4 = 0;
            record->unknown_dc = record->PlayCursor;
            Debug_Printf("Restored buffer\n");
            if (retries-- == 0) {
                Debug_Printf("Failed to lock buffer\n");
                goto finish;
            }
        }
        locked = 1;
        if (audio2 != 0 || bytes1 != (DWORD)size || bytes2 != 0) {
            Debug_Printf("Buffer management out by %d bytes\n", bytes2);
            goto unlock;
        }
        {
            char *destination = (char *)audio1;
            while (size != 0) {
                int chunk = size;
                if (record->unknown_2c == 0) {
                    record->unknown_2c = -1;
                    if (record->unknown_cc == 0) {
                        record->Channel->unknown_next_block_15c(record->Channel);
                        record->unknown_cc = 1;
                    }
                    if (record->Channel->unknown_174 == 0 && record->unknown_a8 == 0) {
                        record->Channel->unknown_end_of_source_160(record->Channel);
                        if (record->Channel->unknown_174 != 0) {
                            Audio_DS_Setup_Decoder(record);
                        }
                    }
                    if (record->Channel->unknown_174 != 0) {
                        record->unknown_cc = 0;
                        record->unknown_28 = record->Channel->unknown_170;
                        record->unknown_20 = record->Channel->unknown_170;
                        record->unknown_2c = record->unknown_24 = record->Channel->unknown_174;
                    }
                    if (record->unknown_2c == 0) {
                        record->unknown_2c = -1;
                    }
                }
                if (record->unknown_2c <= 0 && record->unknown_a8 == 0) {
                    if (record->Channel->Format.BytesPerSample == 2) {
                        memset(destination, 0, chunk);
                    } else {
                        memset(destination, 0x80, chunk);
                    }
                    record->unknown_3c -= chunk;
                } else {
                    int consumed = record->unknown_2c;
                    if (consumed <= 0) {
                        if (!record->Decode(record, destination, &chunk, 0, 0)) {
                            goto unlock;
                        }
                        consumed = 0;
                        record->unknown_2c = 0;
                    } else {
                        if (!record->Decode(record, destination, &chunk, (void const *)record->unknown_28, &consumed)) {
                            goto unlock;
                        }
                    }
                    record->unknown_28 += consumed;
                    record->unknown_2c -= consumed;
                    record->unknown_08 += chunk;
                }
                destination += chunk;
                record->PlayCursor += chunk;
                record->unknown_38 -= chunk;
                size -= chunk;
                written += chunk;
            }
        }
        bytes -= written;
        if (bytes <= 0) {
            break;
        }
    }
    result = 1;
finish:
    if (!locked) {
        return result;
    }
unlock:
    record->Buffer->Unlock(audio1, bytes1, audio2, bytes2);
    return result;
}
