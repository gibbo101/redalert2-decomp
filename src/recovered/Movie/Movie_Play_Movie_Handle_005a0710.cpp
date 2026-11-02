// void __fastcall Play_Movie_Handle(char const *name) (0x005A0710)
// Opens the movie on the hidden surface, clears the screen, plays it with the game sound paused and
// deletes it.
#include "shared/play_movie.hpp"
#include "shared/movie.hpp"
#include "shared/dsurface.hpp"
#include "shared/audio.hpp"
#include "shared/audio_pause.hpp"
#include "shared/gscreen.hpp"
#include "shared/keyboard.hpp"
// @ref ?Create_Movie_Handle@@YIPAVMovieHandle@@PBDPAVSurface@@PBVRect@@@Z=005a1d30

void __fastcall Play_Movie_Handle(char const *name)
{
    MovieHandle *movie = Create_Movie_Handle(name, unknown_surface_839954, 0);
    if (movie != 0) {
        unknown_surface_839954->Fill(0);
        GScreenClass::Blit(true, unknown_surface_839954);
        WWKeyboard->Clear();
        Unknown_Audio_Pause_005a0b10();
        movie->Play();
        Unknown_Audio_Resume_005a0ac0();
        WWKeyboard->Clear();
        delete movie;
    }
}
// @ref ?Audio_Global_Levels@@3PAPAUAudioLevelSet@@A=0083144c
// @ref ?Audio_Streams_Fade_In@@YAXXZ=004082f0
// @ref ?Audio_Streams_Hold@@YAXXZ=00408120
// @ref ?Audio_Streams_Pause@@YAXXZ=00408190
// @ref ?Audio_Streams_Release@@YAXXZ=00408150
// @ref ?Audio_Streams_Resume@@YAXXZ=00408210
// @ref ?Blit@GScreenClass@@SIX_NPAVSurface@@PBVRect@@@Z=004e0c90
// @ref ?Clear@WWKeyboardClass@@QAEXXZ=005329f0
// @ref ?Set_Target@AudioLevel@@QAIXH@Z=004070a0
// @ref ?Speech_Hold@@YAXXZ=00716980
// @ref ?WWKeyboard@@3PAVWWKeyboardClass@@A=00832468
// @ref ?unknown_audio_paused_a7101c@@3_NA=00a7101c
// @ref ?unknown_surface_839954@@3PAVSurface@@A=00839954
// @ref ?unknown_tick_sound@@YAXXZ=007169f0
