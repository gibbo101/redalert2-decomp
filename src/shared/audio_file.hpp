// The audio stream file layer (0x00522B20-0x00522E00, unit before the isometric tile code): one stdio file
// feeding a ring queue, guarded by a critical section. Placeholders named by address until recovered.
#ifndef RA2_SHARED_AUDIO_FILE_HPP
#define RA2_SHARED_AUDIO_FILE_HPP

#include "shared/audio.hpp"

extern CRITICAL_SECTION unknown_audio_file_lock_a52280;     // 0x00A52280
extern "C" int DAT_00a522ac;                    // 0x00A522AC the file's mode (1: read at close, 2: opened to read)
extern "C" int DAT_00a522b0;                    // 0x00A522B0 the layer is set up
extern "C" int DAT_00a522c4;                    // 0x00A522C4
extern "C" AudioQueue *DAT_00a522c8;            // 0x00A522C8 the queue the opened file feeds
extern "C" AudioQueue *DAT_00a522cc;            // 0x00A522CC the queue the open file is flushed into
extern "C" void *DAT_00a522d0;                  // 0x00A522D0 the open stdio file
extern "C" int DAT_00a522d4;                    // 0x00A522D4 set when the first fill failed
extern CRITICAL_SECTION unknown_audio_file_lock_a52268;     // 0x00A52268 (deleted with 0x00A52280)
extern "C" void *DAT_00a522b4;                  // 0x00A522B4 a block freed at shutdown
extern "C" int DAT_00a522b8;                    // 0x00A522B8
extern "C" int DAT_00a522bc;                    // 0x00A522BC the two critical sections exist
extern "C" int DAT_00a522c0;                    // 0x00A522C0 the file thread runs
extern "C" int volatile DAT_00a521e0;           // 0x00A521E0 set to ask the file thread to stop
extern "C" int volatile DAT_00a521e8;           // 0x00A521E8 set by the file thread when it stops
extern "C" HANDLE DAT_00a52260;                 // 0x00A52260 the file thread
extern "C" int DAT_00a521dc;                    // 0x00A521DC entries of the block 0x00A522B4
extern "C" int DAT_00a522d8;                    // 0x00A522D8 the id Audio_File_Find found last
extern "C" int DAT_00a522dc;                    // 0x00A522DC its index
extern "C" DWORD DAT_00a52264;                  // 0x00A52264 the file thread's id
// The file ("Streamer") thread's state (0x00A521E0, passed to Audio_File_Thread; Audio_File_Init and
// Audio_File_Shutdown address its members as the globals above and below). Names are hypotheses.
struct AudioFileThread {
    int volatile Stop;              // +0x00 0x00A521E0 set to ask the thread to stop
    int volatile Passes;            // +0x04 0x00A521E4 loop passes
    int volatile Stopped;           // +0x08 0x00A521E8 set by the thread when it stops
    int unknown_0c;                 // +0x0C
    __int64 volatile Period;        // +0x10 0x00A521F0 the pass period in milliseconds (100)
    int volatile Running;           // +0x18 0x00A521F8 set by the thread when it starts
    int unknown_1c;                 // +0x1C
    AudioTimeSpan Timing;           // +0x20 0x00A52200
};
extern "C" int volatile DAT_00a521e4;           // 0x00A521E4
extern "C" __int64 volatile DAT_00a521f0;       // 0x00A521F0
extern "C" int volatile DAT_00a521f8;           // 0x00A521F8
extern "C" AudioTimeSpan DAT_00a52200;          // 0x00A52200
// Sets the layer up: the locks, the block of count ids (0x00A522B4, the main window entered), the file
// thread, the ring and its two queues of at least 0x2800 bytes; on failure shuts it down (0x00522560).
int __fastcall Audio_File_Init(int count, int size);
// The file thread: every Period milliseconds tops up the read queue from the stream file (mode 2) or
// flushes the write queue into it (mode 1) (0x005227D0).
DWORD WINAPI Audio_File_Thread(void *data);
// Stops the layer: flushes and closes the stream file, stops the file thread, releases the queues and the
// ring, deletes the locks (0x00522930; __fastcall: Audio_File_Init's failure path schedules its xor eax, eax
// before the pops only then).
void __fastcall Audio_File_Shutdown();
// The index of id in the block 0x00A522B4 (cached), or -1 (0x00522BD0).
int __fastcall Audio_File_Find(int id);
// Flushes the stream file into its queue while it is being read (0x00522E10).
void Audio_File_Flush();

#endif
