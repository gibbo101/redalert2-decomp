// bool CD::Swap_Disk(int cd) (0x0046E750, slot 2)
// Switches to another game disk: stops the music, releases the five per-disk
// mixfiles and, when the disk's volume checks out, reopens MAIN.MIX,
// MAPS<n>.MIX, MULTI.MIX, THEME.MIX (rescanning the themes) and
// MOVIES<n>.MIX for disk n = cd + 1. False when an archive cannot be
// created; true without reopening when the volume check fails.
// Assumes: the global names, FastKey and VolumeCheck's result meaning are
// hypotheses; the theme save mirrors Insert_Disk.
#include "shared/cd.hpp"
#include "shared/mix_file_class.hpp"
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ?Theme@@3VThemeClass@@A=00a35d78
// @ref ?Stop@ThemeClass@@QAEX_N@Z=006e81a0
// @ref ?Scan@ThemeClass@@QAEXXZ=006e7af0
// @ref ?VolumeCheck@@YA_NXZ=00715090
// @ref ??0?$MixFileClass@VCCFileClass@@@@QAE@PBDPBVPKey@@@Z=005952f0
// @ref ?FastKey@@3VPKey@@A=00839010
// @ref ?MoviesMix@@3PAV?$MixFileClass@VCCFileClass@@@@A=008374d4
// @ref ?ThemeMix@@3PAV?$MixFileClass@VCCFileClass@@@@A=00831448
// @ref ?MultiMix@@3PAV?$MixFileClass@VCCFileClass@@@@A=00837498
// @ref ?MapsMix@@3PAV?$MixFileClass@VCCFileClass@@@@A=008374f4
// @ref ?MainMix@@3PAV?$MixFileClass@VCCFileClass@@@@A=008374dc
// @ref ??_C@_0CB@GBBB@?$CK?$CK?$CK?$CK?$CK?5Swapping?5to?5disk?5?$CFd?5?$CK?$CK?$CK?$CK?$CK?6@=007d221c
// @ref ??_C@_0BD@MGDA@?5?5?5?5?5Releasing?5?$CFs?6?$AA@=007d2208
// @ref ??_C@_08DAIP@MAIN?4MIX?$AA@=007d21fc
// @ref ??_C@_0BF@OLAF@?5?5?5?5?5Initialized?5?$CFs?6?$AA@=007d21e4
// @ref ??_C@_0N@GFJE@MAPS?$CF02d?4MIX?$AA@=007d21d4
// @ref ??_C@_0BG@HMGE@?5?5?5?5?5Initializing?5?$CFs?6?$AA@=007d21bc
// @ref ??_C@_0O@HDKF@?5?5?5?5?5FAILED?$CB?6?$AA@=007d21ac
// @ref ??_C@_0BN@MGOF@?5?5?5?5?5Initializing?5Multi?4Mix?6?$AA@=007d218c
// @ref ??_C@_09MIH@MULTI?4MIX?$AA@=007d2180
// @ref ??_C@_0BO@IFKA@?5?5?5?5?5Initializing?5Themes?4MIX?6?$AA@=007d2160
// @ref ??_C@_09OKCB@THEME?4MIX?$AA@=007d2154
// @ref ??_C@_0P@CLBG@MOVIES?$CF02d?4MIX?$AA@=007d2144

bool CD::Swap_Disk(int cd)
{
    char name[64];

    Debug_Printf("***** Swapping to disk %d *****\n", cd);

    if (LastTheme == THEME_NONE) {
        ThemeType theme = Theme.Score;
        if (theme == THEME_NONE) {
            theme = Theme.Pending;
        }
        LastTheme = theme;
    }
    Theme.Stop();

    if (MoviesMix != 0) {
        Debug_Printf("     Releasing %s\n", MoviesMix->Filename);
        delete MoviesMix;
        MoviesMix = 0;
    }
    if (ThemeMix != 0) {
        Debug_Printf("     Releasing %s\n", ThemeMix->Filename);
        delete ThemeMix;
        ThemeMix = 0;
    }
    if (MultiMix != 0) {
        Debug_Printf("     Releasing %s\n", MultiMix->Filename);
        delete MultiMix;
        MultiMix = 0;
    }
    if (MapsMix != 0) {
        Debug_Printf("     Releasing %s\n", MapsMix->Filename);
        delete MapsMix;
        MapsMix = 0;
    }
    if (MainMix != 0) {
        Debug_Printf("     Releasing %s\n", MainMix->Filename);
        delete MainMix;
        MainMix = 0;
    }

    if (!VolumeCheck()) {
        return true;
    }

    MainMix = new MixFileClass<CCFileClass>("MAIN.MIX", &FastKey);
    Debug_Printf("     Initialized %s\n", MainMix->Filename);

    cd++;
    sprintf(name, "MAPS%02d.MIX", cd);
    Debug_Printf("     Initializing %s\n", name);
    MapsMix = new MixFileClass<CCFileClass>(name, &FastKey);
    if (MapsMix == 0) {
        Debug_Printf("     FAILED!\n");
        return false;
    }

    Debug_Printf("     Initializing Multi.Mix\n");
    MultiMix = new MixFileClass<CCFileClass>("MULTI.MIX", &FastKey);
    if (MultiMix == 0) {
        Debug_Printf("     FAILED!\n");
        return false;
    }

    Debug_Printf("     Initializing Themes.MIX\n");
    ThemeMix = new MixFileClass<CCFileClass>("THEME.MIX", &FastKey);
    Theme.Scan();

    sprintf(name, "MOVIES%02d.MIX", cd);
    Debug_Printf("     Initializing %s\n", name);
    MoviesMix = new MixFileClass<CCFileClass>(name, &FastKey);
    if (MoviesMix == 0) {
        Debug_Printf("     FAILED!\n");
        return false;
    }

    return VolumeCheck();
}
