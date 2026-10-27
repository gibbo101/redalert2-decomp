// void OptionsClass::Unlock_Movie(char const *name) (0x005DA3F0)
// A campaign movie that has been played raises its campaign's last unlocked
// movie (Soviet list first, then Allied).
// @ref ?AlliedMovies@@3PAUMovieEntryStruct@@A=007e8258
// @ref ?SovietMovies@@3PAUMovieEntryStruct@@A=007e82f8
// @ref __stricmp=00781f20
#include "shared/options.hpp"
#include "shared/abstract_type.hpp"

// The index of a named movie in a list, or -1.
inline int Movie_Index(MovieEntryStruct const *movies, char const *name)
{
    for (int index = 0; movies->Name != 0; index++, movies++) {
        if (_stricmp(name, movies->Name) == 0) {
            return index;
        }
    }
    return -1;
}

void OptionsClass::Unlock_Movie(char const *name)
{
    int index = Movie_Index(SovietMovies, name);
    if (index > UnlockedMovie[0]) {
        UnlockedMovie[0] = index;
    }
    index = Movie_Index(AlliedMovies, name);
    if (index > UnlockedMovie[1]) {
        UnlockedMovie[1] = index;
    }
}
