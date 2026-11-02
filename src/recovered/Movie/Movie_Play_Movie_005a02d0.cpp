// void __fastcall Play_Movie(char const *name, int theme, bool clrscrn_after, bool stretch, bool clrscrn_before, bool bink_flag) (0x005A02D0)
// TibSun's Play_Movie with RA2's Bink branch: the game sound is paused around both players.
#include "shared/play_movie.hpp"
#include "shared/movie.hpp"
#include "shared/dsurface.hpp"
#include "shared/movie_globals.hpp"
#include "shared/audio.hpp"
#include "shared/audio_pause.hpp"
#include "shared/gscreen.hpp"
#include "shared/map_view.hpp"
#include "shared/mouse.hpp"
#include "shared/keyboard.hpp"
#include "shared/options.hpp"
#include "shared/hicolor.hpp"
#include "shared/crt_string.hpp"
#include "shared/debug_printf.hpp"
// @ref ?Find_Movie_File@@YI_NPBDPADH@Z=005a1bb0
// @ref ?unknown_game_mode_a3d298@@3HA=00a3d298
// @ref ?WWKeyboard@@3PAVWWKeyboardClass@@A=00832468
// @ref ?Clear@WWKeyboardClass@@QAEXXZ=005329f0
// @ref _strrchr=00781ff0
// @ref __stricmp=00781f20
// @ref ??_C@_04LMEE@?4bik?$AA@=007e329c
// @ref ??_C@_0BH@CNON@Play_Movie?$CI?$CJ?5as?5Bink?$CB?6?$AA@=007e3284
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ?WWMouse@@3PAVMouse@@A=00839c68
// @ref ?unknown_surface_839954@@3PAVSurface@@A=00839954
// @ref ?Blit@GScreenClass@@SIX_NPAVSurface@@PBVRect@@@Z=004e0c90
// @ref ??0BinkClass@@QAE@PBD@Z=0042fe70
// @ref ??1BinkClass@@QAE@XZ=0042fee0
// @ref ?Unknown_00430430@BinkClass@@QAEXXZ=00430430
// @ref ?unknown_audio_paused_a7101c@@3_NA=00a7101c
// @ref ?Speech_Hold@@YAXXZ=00716980
// @ref ?Audio_Streams_Hold@@YAXXZ=00408120
// @ref ?Audio_Streams_Pause@@YAXXZ=00408190
// @ref ?Audio_Streams_Release@@YAXXZ=00408150
// @ref ?Audio_Streams_Resume@@YAXXZ=00408210
// @ref ?Audio_Streams_Fade_In@@YAXXZ=004082f0
// @ref ?Audio_Global_Levels@@3PAPAUAudioLevelSet@@A=0083144c
// @ref ?Set_Target@AudioLevel@@QAIXH@Z=004070a0
// @ref ?unknown_tick_sound@@YAXXZ=007169f0
// @ref ?Audio_Pause@@YIXXZ=00406de0
// @ref ?Audio_Resume@@YAXXZ=00406e00
// @ref ?Audio_DS_Set_Primary_Format@@YIXHHH@Z=0040a6e0
// @ref ?Audio_DS_Apply_Primary_Format@@YIXXZ=0040a770
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Flag_To_Redraw@GScreenClass@@UAEXH@Z=004e09a0
// @ref ?Options@@3VOptionsClass@@A=00a40b18
// @ref __real@8@4006ff00000000000000=007a2f50
// @ref __ftol=0077f110
// @ref ?unknown_surface_839958@@3PAVSurface@@A=00839958
// @ref ?VQA_Unknown_005A1010@@YIPAVVQAMovie@@PBDPAVSurface@@VRect@@2H_N@Z=005a1010
// @ref ?Unknown_0071D300@VQAClass@@QAEHXZ=0071d300
// @ref ?Unknown_0071D310@VQAClass@@QAEHXZ=0071d310
// @ref ?VQA_Movie_Close@@YIXPAVVQAMovie@@@Z=005a1470
// @ref ??1VQAMovie@@QAE@XZ=005a1760
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ?AllowStretchBlits_852fd6@@3_NA=00852fd6
// @ref ?unknown_int_839648@@3HA=00839648
// @ref ?unknown_int_83964c@@3HA=0083964c
// @ref ?VQA_Movie_Play@@YIXPAVVQAMovie@@_NH1@Z=005a14d0
// @ref ??_C@_0CB@LNKL@Stretching?5movie?5?$CFdx?$CFd?5?9?$DO?5?$CFdx?$CFd?6@=007e3260

void __fastcall Play_Movie(char const *name, int theme, bool clrscrn_after, bool stretch, bool clrscrn_before,
                           bool bink_flag)
{
    char filename[256];

    if (!Find_Movie_File(name, filename, 1)) {
        return;
    }

    if (unknown_game_mode_a3d298 != 0) {
        return;
    }

    WWKeyboard->Clear();

    char *extension = strrchr(filename, '.');
    if (extension != 0 && _stricmp(extension, ".bik") == 0) {
        Debug_Printf("Play_Movie() as Bink!\n");
        WWMouse->Hide_Mouse();
        if (clrscrn_before) {
            unknown_surface_839954->Fill(0);
            GScreenClass::Blit(true, unknown_surface_839954);
        }

        BinkClass bink(filename);
        if (bink_flag == true) {
            bink.unknown_00 = true;
        }
        Unknown_Audio_Pause_005a0b10();
        Audio_Pause();
        Audio_DS_Set_Primary_Format(44100, 16, 2);
        bink.Unknown_00430430();
        Audio_DS_Apply_Primary_Format();
        Audio_Resume();
        Unknown_Audio_Resume_005a0ac0();

        if (clrscrn_after == true) {
            unknown_surface_839954->Fill(0);
            GScreenClass::Blit(true, unknown_surface_839954);
        }
        WWKeyboard->Clear();
        WWMouse->Show_Mouse();
        Map.Flag_To_Redraw(2);
        return;
    }

    WWKeyboard->Clear();
    VQAMovie *vqa = VQA_Unknown_005A1010(filename, unknown_surface_839958, Rect(0, 0, 0, 0), Rect(0, 0, 0, 0),
                                         int(Options.VoiceVolume * 255.0), 1);
    if (vqa != 0) {
        if (vqa->Player->Unknown_0071D300() < 320 && vqa->Player->Unknown_0071D310() < 200) {
            VQA_Movie_Close(vqa);
            delete vqa;
            return;
        }

        bool dostretch = (stretch == true && Options.StretchMovies == true);
        if (AllowStretchBlits_852fd6 == true && dostretch == true) {
            if (vqa->Source.Width < unknown_int_839648 && vqa->Source.Height < unknown_int_83964c) {
                float ratio = ((float)unknown_int_839648 / (float)vqa->Source.Width);
                vqa->Dest.Width = unknown_int_839648;
                vqa->Dest.Height = (int)(vqa->Source.Height * ratio);
                vqa->Dest.X = 0;
                vqa->Dest.Y = (unknown_int_83964c - vqa->Dest.Height) / 2;
                Debug_Printf("Stretching movie %dx%d -> %dx%d\n", vqa->Source.Width, vqa->Source.Height, vqa->Dest.Width, vqa->Dest.Height);
            }
        }

        WWMouse->Hide_Mouse();
        if (clrscrn_before) {
            unknown_surface_839954->Fill(0);
            GScreenClass::Blit(true, unknown_surface_839954);
        }
        Unknown_Audio_Pause_005a0b10();
        Audio_Pause();
        Audio_DS_Set_Primary_Format(44100, 16, 2);
        VQA_Movie_Play(vqa, true, theme, false);
        Audio_DS_Apply_Primary_Format();
        Audio_Resume();
        Unknown_Audio_Resume_005a0ac0();
        VQA_Movie_Close(vqa);
        delete vqa;

        if (clrscrn_after == true) {
            unknown_surface_839954->Fill(0);
            GScreenClass::Blit(true, unknown_surface_839954);
        }
        WWMouse->Show_Mouse();
        Map.Flag_To_Redraw(2);
        WWKeyboard->Clear();
    }
}
