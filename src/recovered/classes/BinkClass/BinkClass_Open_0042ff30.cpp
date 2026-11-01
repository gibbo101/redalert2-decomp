// bool BinkClass::Open(char const *filename) (0x0042FF30)
// Opens the movie as a file or from inside a mixfile, sets its volume and
// frame interval, picks the target surface (the screen surface centred in
// the window client area unless a companion is present), clips the movie
// rectangle to the target and records the screen's Bink surface type.
#include "shared/movie.hpp"
#include "shared/dsurface.hpp"
#include "shared/raw_file_class.hpp"
#include "shared/cc_file_class.hpp"
#include "shared/mix_file_class.hpp"
// @ref ??_C@_0BA@BOHO@Bink?5Error?3?5?$CFs?6?$AA@=007cf4d8
// @ref ?unknown_check_406f30@@YAHXZ=00406f30
// @ref ?unknown_directsound_40a6c0@@YAPAXXZ=0040a6c0
// @ref ?unknown_volume_a40b48@@3MA=00a40b48
// @ref ?unknown_volume_84e9a8@@3MA=0084e9a8
// @ref ?unknown_create_companion_69b190@@YIPAVVQAMovieCompanion@@PBD@Z=0069b190
// @ref ?unknown_surface_839950@@3PAVSurface@@A=00839950
// @ref ?unknown_surface_839954@@3PAVSurface@@A=00839954
// @ref ?MainWindow@@3PAUHWND__@@A=00b263d8
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref __real@4@400e8000000000000000=0079c780
// @ref ??0Rect@@QAE@HHHH@Z=0042bcd0
// @ref ?Intersect@@YI?AVRect@@ABV1@0PAH1@Z=0041fdf0


bool BinkClass::Open(char const *filename)
{
    Close();
    if (unknown_check_406f30()) {
        BinkSetSoundSystem((void *)BinkOpenDirectSound, (unsigned long)unknown_directsound_40a6c0());
    }
    if (RawFileClass(filename).Is_Available() == true) {
        Handle = BinkOpen(filename, 0);
    } else {
        long offset = 0;
        MixFileClass<CCFileClass> *mixfile = 0;
        if (MixFileClass<CCFileClass>::Offset(filename, 0, &mixfile, &offset, 0) == true) {
            File = CreateFileA(mixfile->Filename, 0x80000000, 3, 0, 3, 0x8000080, 0);
            if (File != INVALID_HANDLE_VALUE) {
                SetFilePointer(File, offset, 0, 0);
                Handle = BinkOpen((char const *)File, 0x800000);
            }
        }
    }
    if (Handle == 0) {
        Debug_Printf("Bink Error: %s\n", BinkGetError());
        return false;
    }
    *(int *)&unknown_volume_84e9a8 = *(int *)&unknown_volume_a40b48;
    BinkSetVolume(Handle, (int)(unknown_volume_84e9a8 * 32768.0f));
    unknown_24 = 60 / (Handle->FrameRate / Handle->FrameRateDiv);
    Companion = unknown_create_companion_69b190(filename);
    Rect movie(0, 0, Handle->Width, Handle->Height);
    if (Target == 0) {
        if (Companion != 0 && *(int *)Companion != 0) {
            Target = unknown_surface_839954;
            movie.X = (Target->Get_Width() - movie.Width) / 2;
            movie.Y = (Target->Get_Height() - movie.Height) / 2;
        } else {
            Target = unknown_surface_839950;
            RECT client;
            GetClientRect(MainWindow, &client);
            int clientwidth = client.right - client.left;
            int clientheight = client.bottom - client.top;
            movie.X = (clientwidth - movie.Width) / 2;
            movie.Y = (clientheight - movie.Height) / 2;
        }
    }
    Area = Target->Get_Rect().Intersect(movie);
    SurfaceType = BinkDDSurfaceType(((DSurface *)unknown_surface_839950)->Get_DD_Surface());
    return true;
}
