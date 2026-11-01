// bool BinkClass::Unknown_00430600(Surface *surface, int x, int y) (0x00430600)
// Follows the volume setting, pauses or resumes the movie with the
// application focus, then decodes and copies every due frame into `surface`
// at x, y; false when no frame was due.
#include "shared/movie.hpp"
// @ref ??_C@_0BC@FLCF@Pause?5bink?5movie?6?$AA@=007cf4fc
// @ref ??_C@_0BD@CJNA@Resume?5bink?5movie?6?$AA@=007cf4e8
// @ref ?unknown_flag_a40d28@@3_NA=00a40d28
// @ref ?Unknown_0069B420@VQAMovieCompanion@@QAE_NH@Z=0069b420
// @ref ?Unknown_004309B0@BinkClass@@QAEXPAVSurface@@HH_N@Z=004309b0
// @ref ?Unknown_00430A30@BinkClass@@QAEXPAVSurface@@@Z=00430a30
// @ref ?Unknown_00430AF0@BinkClass@@QAEXPAVSurface@@@Z=00430af0

extern bool unknown_flag_a40d28;                // 0x00A40D28 application active (focus)

bool BinkClass::Unknown_00430600(Surface *surface, int x, int y)
{
    if (unknown_volume_84e9a8 != unknown_volume_a40b48) {
        // Copied as a bit pattern: the original moves it through eax and reads the copy back.
        *(int *)&unknown_volume_84e9a8 = *(int *)&unknown_volume_a40b48;
        BinkSetVolume(Handle, (int)(unknown_volume_84e9a8 * 32768.0f));
    }
    if (!unknown_flag_a40d28) {
        if (unknown_2c == true) {
            Debug_Printf("Pause bink movie\n");
            unknown_2c = false;
            BinkPause(Handle, 1);
        }
    } else if (!unknown_2c) {
        Debug_Printf("Resume bink movie\n");
        unknown_2c = true;
        BinkPause(Handle, 0);
        if (Target == unknown_surface_839950) {
            RECT client;
            GetClientRect(MainWindow, &client);
            ClientToScreen(MainWindow, (POINT *)&client);
            Unknown_004309B0(Target, Area.X + client.left, Area.Y + client.top, true);
        } else {
            Unknown_004309B0(Target, Area.X, Area.Y, true);
        }
    }
    if (!unknown_2d) {
        bool due = BinkWait(Handle) == 0;
        if (!due) {
            return due;
        }
    }
    do {
        BinkDoFrame(Handle);
        unknown_2d = false;
        bool special = false;
        if (Companion != 0) {
            special = Companion->Unknown_0069B420(Handle->FrameNum * unknown_24);
            if (special) {
                Unknown_00430AF0(surface);
            }
        }
        void *buffer = surface->Lock();
        if (buffer != 0) {
            int pitch = surface->Stride();
            int height = surface->Get_Height();
            unsigned flags = SurfaceType;
            if (special) {
                flags |= 0x80000000;
            }
            BinkCopyToBuffer(Handle, buffer, pitch, height, x, y, flags);
            surface->Unlock();
        }
        Unknown_00430A30(surface);
        BinkNextFrame(Handle);
    } while (BinkWait(Handle) == 0);
    return true;
}
