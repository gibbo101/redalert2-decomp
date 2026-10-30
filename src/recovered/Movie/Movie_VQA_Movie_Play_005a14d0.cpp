// void __fastcall VQA_Movie_Play(VQAMovie *movie, bool hide, int theme, bool unknown) (0x005A14D0)
// Plays the movie to the end (or Repeats times) unless another one is
// playing; optionally brackets it with WWMouse Hide_Mouse/Show_Mouse and
// starts theme first.
// @ref ?CurrentVQAMovie@@3PAVVQAMovie@@A=00a710ac
// @ref ?VQA_Unknown_0071DBA0@@YI_NH@Z=0071dba0
// @ref ?Unknown_0071CBE0@VQAClass@@QAE_NHH@Z=0071cbe0
// @ref ?Unknown_0071CC10@VQAClass@@QAE_NHHH@Z=0071cc10
// @ref ?Unknown_0071CC60@VQAClass@@QAEXH@Z=0071cc60
// @ref ?Unknown_0071CCD0@VQAClass@@QAEHH_N@Z=0071ccd0
// @ref ?Unknown_0071D210@VQAClass@@QAEXXZ=0071d210
// @ref ?WWMouse@@3PAVMouse@@A=00839c68
// @ref ?Theme@@3VThemeClass@@A=00a35d78
// @ref ?Queue_Song@ThemeClass@@QAEXH@Z=006e7e20
#include "shared/movie.hpp"
#include "shared/movie_globals.hpp"

VQAMovie *CurrentVQAMovie;      // 0x00A710AC: the VQA movie playing now

void __fastcall VQA_Movie_Play(VQAMovie *movie, bool hide, int theme, bool unknown)
{
    if (CurrentVQAMovie) {
        return;
    }

    movie->Playing = true;
    CurrentVQAMovie = movie;
    int start = 0;
    int unknown2 = -1;
    int repeats = 0;
    if (VQA_Unknown_0071DBA0(2)) {
        start = movie->unknown_10;
        if (movie->unknown_14 >= 0) {
            unknown2 = movie->unknown_14;
        }
        repeats = movie->Repeats;
        if (movie->Mode == 1) {
            if (movie->unknown_18 == 0) {
                movie->Player->Unknown_0071CBE0(movie->unknown_20, repeats);
            } else {
                movie->Player->Unknown_0071CC10(start, unknown2, repeats);
            }
        }
    }

    if (hide) {
        WWMouse->Hide_Mouse();
    }
    if (theme != -1) {
        Theme.Queue_Song(theme);
    }

    do {
        if (movie->Mode == 2 || start) {
            movie->Player->Unknown_0071CC60(start);
        }
        int result = movie->Player->Unknown_0071CCD0(unknown2, unknown);
        if (movie->Mode == 1) {
            repeats = 0;
        }
        movie->Player->Unknown_0071D210();
        if (result == 1) {
            break;
        }
        if (repeats > 0) {
            repeats--;
        }
    } while (repeats != 0);

    if (hide) {
        WWMouse->Show_Mouse();
    }
    CurrentVQAMovie = 0;
}
