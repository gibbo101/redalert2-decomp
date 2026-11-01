// int __fastcall Audio_Stream_Open(AudioStreamPlayer *stream, char const *name, int raw) -- 0x00407A90
// Purpose: starts the stream playing the sound file name (a stream that is
// held is left alone): stops its channel, opens the file (a RawFileClass
// first unless raw, otherwise the mixfile-aware CCFileClass), reads its
// wave format, sizes the ring for the buffered time (0x00408460), reads
// the first block into it (the byte count of the read reuses raw's
// slot), points the channel's source at what was read, sets the volume
// to full and starts the channel. Returns 1 when playing, 0 on any
// failure (queues released).
#include "shared/cc_file_class.hpp"
#include "shared/audio.hpp"

void *__cdecl operator new(unsigned int size);
void __cdecl operator delete(void *block);

int __fastcall Audio_Stream_Open(AudioStreamPlayer *stream, char const *name, int raw)
{
    if (stream->HoldCount == 0) {
        if (stream->Channel != 0) {
            EnterCriticalSection(&Audio_Stream_Lock);
            Audio_Channel_Stop(stream->Channel);
            LeaveCriticalSection(&Audio_Stream_Lock);
        }
        if (stream->File != 0) {
            delete stream->File;
            stream->File = 0;
        }
        if (raw == 0) {
            stream->File = new RawFileClass(name);
            if (stream->File != 0 && !stream->File->Is_Available(0)) {
                if (stream->File != 0) {
                    delete stream->File;
                }
                stream->File = 0;
            }
        }
        if (stream->File == 0) {
            stream->File = new CCFileClass(name);
        }
        if (stream->File != 0) {
            if (!stream->File->Is_Available(0) || !stream->File->Open(FILE_RIGHTS_READ)) {
                if (stream->File != 0) {
                    delete stream->File;
                }
                stream->File = 0;
            } else if (Audio_Format_Read_Wave(stream->File, &stream->Format, &stream->DataSize)) {
                stream->Remaining = stream->DataSize;
                stream->DataStart = stream->File->Seek(0, 1);
                if (stream->Fill != 0) {
                    Audio_Queue_Release(stream->Fill);
                    stream->Fill = 0;
                }
                if (stream->Drain != 0) {
                    Audio_Queue_Release(stream->Drain);
                    stream->Drain = 0;
                }
                AudioStream *ring = stream->Ring;
                __int64 buffered = stream->BufferTime;
                int ring_bytes = stream->Format.Bytes_For_Time(buffered);
                stream->unknown_a0 = stream->Format.Bytes_For_Time(stream->Channel->unknown_1a8 * 2);
                if (Audio_Ring_Size(ring) != ring_bytes) {
                    Audio_Ring_Clear(ring);
                    AudioStreamNode *node = Audio_Ring_Node_Create(ring_bytes, 0);
                    if (node != 0) {
                        Audio_Ring_Add_Node(ring, node);
                    }
                }
                if (Audio_Ring_Size(ring) == ring_bytes) {
                    Audio_Ring_Reset(stream->Ring);
                    stream->Fill = Audio_Ring_Acquire(stream->Ring, 0);
                    stream->Drain = Audio_Ring_Acquire(stream->Ring, 1);
                    if (stream->Fill != 0 && stream->Drain != 0) {
                        unsigned __int64 time = stream->Channel->unknown_1b0 * 2;
                        unsigned __int64 first = time > (unsigned __int64)(Audio_Streamer.Interval * 4) ? time : Audio_Streamer.Interval * 4;
                        if (first <= 4000) {
                            first = 4000;
                        }
                        EnterCriticalSection(&Audio_Stream_Lock);
                        int bytes;
                        if (first != 0) {
                            bytes = stream->Format.Bytes_For_Time(first);
                            if (bytes > stream->Remaining) {
                                bytes = stream->Remaining;
                            }
                        } else {
                            bytes = stream->Remaining;
                        }
                        Audio_Stream_In_Read = true;
                        int result = Audio_Queue_File(stream->Fill, stream->File, bytes, &raw);
                        Audio_Stream_In_Read = false;
                        stream->Remaining -= raw;
                        if (stream->Remaining <= 0 || result == 2 || result == 0) {
                            stream->Flags &= ~AUDIO_STREAM_FILLING;
                        }
                        LeaveCriticalSection(&Audio_Stream_Lock);
                        if (raw != 0) {
                            Audio_Queue_Ready(stream->Drain);
                            stream->Source.unknown_00 = (int)stream->Drain->Pointer;
                            stream->Source.unknown_04 = stream->Format.Bytes_For_Time(stream->Channel->unknown_1a8);
                            if (stream->Source.unknown_04 > stream->Drain->Available) {
                                stream->Source.unknown_04 = stream->Drain->Available;
                            }
                            stream->unknown_90 = stream->Source.unknown_04;
                            stream->Source.Format = &stream->Format;
                            stream->Channel->Levels.Volume.Set(0x4000);
                            Audio_Channel_Set_Source(stream->Channel, &stream->Source);
                            stream->Flags |= AUDIO_STREAM_PLAYING;
                            if (Audio_Channel_Start(stream->Channel) != 0) {
                                stream->Flags &= ~AUDIO_STREAM_PLAYING;
                                Audio_Queue_Release(stream->Fill);
                                stream->Fill = 0;
                                Audio_Queue_Release(stream->Drain);
                                stream->Drain = 0;
                            } else {
                                stream->StartTime = Audio_Now();
                                stream->unknown_20 = stream->StartTime;
                                stream->Flags |= AUDIO_STREAM_FILLING;
                                return 1;
                            }
                        }
                    }
                }
            }
        }
        if (stream->Fill != 0) {
            Audio_Queue_Release(stream->Fill);
            stream->Fill = 0;
        }
        if (stream->Drain != 0) {
            Audio_Queue_Release(stream->Drain);
            stream->Drain = 0;
        }
    }
    return 0;
}

