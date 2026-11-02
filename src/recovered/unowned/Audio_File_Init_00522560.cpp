// int __fastcall Audio_File_Init(int count, int size) -- 0x00522560
// Sets the stream file layer up: both locks, a zeroed block of count ids, the file thread's state (period 100,
// its timing statistics), the file thread at priority 2 ("Unable to change the priority of the Streamer
// Thread" otherwise), the ring with one node of at least 0x2800 bytes and its two queues; clears the recorded
// key states and enters the main window into the id block. Any failure shuts the layer down and returns 0.
// Placeholders: the globals are named by address until the layer is recovered.
#include "shared/audio_file.hpp"
#include "shared/crt_memory.hpp"
#include "shared/debug_printf.hpp"
#include "shared/win32_window.hpp"
// @ref ?unknown_audio_file_lock_a52280@@3UCRITICAL_SECTION@@A=00a52280
// @ref ?unknown_audio_file_lock_a52268@@3UCRITICAL_SECTION@@A=00a52268
// @ref ?Audio_File_Thread@@YGKPAX@Z=005227d0
// @ref ??2@YAPAXI@Z=00782017
// @ref __alldiv=007820c0
// @ref ??_C@_0DL@CKCP@Unable?5to?5change?5the?5priority?5of@=007ccd50
extern "C" short DAT_00a51fd0[256];

int __fastcall Audio_File_Init(int count, int size)
{
    InitializeCriticalSection(&unknown_audio_file_lock_a52280);
    InitializeCriticalSection(&unknown_audio_file_lock_a52268);
    DAT_00a522bc = 1;
    if (count <= 0) {
        Audio_File_Shutdown();
        return 0;
    }
    if (size < 0x2800) {
        size = 0x2800;
    }
    DAT_00a522b4 = operator new(count * 4);
    if (DAT_00a522b4 == 0) {
        Audio_File_Shutdown();
        return 0;
    }
    memset(DAT_00a522b4, 0, count * 4);
    DAT_00a522b8 = 0;
    DAT_00a521dc = count;
    DAT_00a521e0 = 0;
    DAT_00a521e8 = 0;
    DAT_00a521f8 = 0;
    DAT_00a521f0 = 100;
    DAT_00a521e4 = 0;
    DAT_00a52200.Reset();
    DAT_00a52200.Set(DAT_00a521f0);
    DAT_00a52200.Set_08(DAT_00a521f0 / 4);
    DAT_00a52200.Set_20(DAT_00a521f0 / 4);
    DAT_00a52260 = CreateThread(0, 0x1000, Audio_File_Thread, (void *)&DAT_00a521e0, 0, &DAT_00a52264);
    if (DAT_00a52260 == 0) {
        Audio_File_Shutdown();
        return 0;
    }
    DAT_00a522c0 = 1;
    if (!SetThreadPriority(DAT_00a52260, 2)) {
        char buffer[1024];
        FormatMessageA(0x1000, 0, GetLastError(), 0, buffer, 1024, 0);
        Debug_Printf("Unable to change the priority of the Streamer Thread - %s\n", buffer);
        Audio_File_Shutdown();
        return 0;
    }
    DAT_00a522c4 = (int)Audio_Ring_Create();
    if (DAT_00a522c4 == 0) {
        Audio_File_Shutdown();
        return 0;
    }
    if (!Audio_Ring_Add_Nodes((AudioStream *)DAT_00a522c4, 1, size, 0)) {
        Audio_File_Shutdown();
        return 0;
    }
    Audio_Ring_Reset((AudioStream *)DAT_00a522c4);
    DAT_00a522c8 = Audio_Ring_Acquire((AudioStream *)DAT_00a522c4, 0);
    DAT_00a522cc = Audio_Ring_Acquire((AudioStream *)DAT_00a522c4, 1);
    if (DAT_00a522c8 == 0 || DAT_00a522cc == 0) {
        Audio_File_Shutdown();
        return 0;
    }
    DAT_00a522b0 = 1;
    memset(DAT_00a51fd0, 0, sizeof(DAT_00a51fd0));
    if (MainWindow != 0) {
        int *ids = (int *)DAT_00a522b4;
        int *free_slot = 0;
        for (int i = 1; i < DAT_00a521dc; i++, ids++) {
            if (*ids == 0) {
                if (free_slot == 0) {
                    free_slot = ids;
                }
            } else if (*ids == (int)MainWindow) {
                return 1;
            }
        }
        if (free_slot != 0) {
            *free_slot = (int)MainWindow;
            DAT_00a522b8++;
        }
    }
    return 1;
}
