// void OptionsClass::Fill_Movie_List(HWND list) (0x005DA470)
// The intro and every unlocked campaign movie go into the list box with
// their entries as item data.
// @ref ??_C@_0BD@LCMK@D?3?2Ra2?2Options?4CPP?$AA@=007e8a48
// @ref ?AlliedMovies@@3PAUMovieEntryStruct@@A=007e8258
// @ref ?IntroMovie@@3UMovieEntryStruct@@A=007e8248
// @ref ?SovietMovies@@3PAUMovieEntryStruct@@A=007e82f8
// @ref __imp__SendMessageA@16=0079a4a0
#include "shared/options.hpp"
#include "shared/string_table.hpp"

// Adds a movie (its label's text) to the list box.
inline void Add_Movie(HWND list, MovieEntryStruct const *movie)
{
    if (movie->Name != 0 && movie->Label != 0) {
        int index = SendMessageA(list, 0x4CD, 0, (LPARAM)StringTable::Load_String(movie->Label, 0, "D:\\Ra2\\Options.CPP", 1248));
        if (index != -1) {
            SendMessageA(list, 0x19A, index, (LPARAM)movie);
        }
    }
}

void OptionsClass::Fill_Movie_List(HWND list)
{
    Add_Movie(list, &IntroMovie);
    if (UnlockedMovie[0] >= 0) {
        int count = UnlockedMovie[0] + 1;
        for (MovieEntryStruct *movie = SovietMovies; movie->Name != 0 && count > 0; movie++, count--) {
            Add_Movie(list, movie);
        }
    }
    if (UnlockedMovie[1] >= 0) {
        int count = UnlockedMovie[1] + 1;
        for (MovieEntryStruct *movie = AlliedMovies; movie->Name != 0 && count > 0; movie++, count--) {
            Add_Movie(list, movie);
        }
    }
}
