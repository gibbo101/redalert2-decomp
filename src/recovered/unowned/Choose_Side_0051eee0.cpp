// void Choose_Side() (0x0051EEE0)
// Plays the intro movie when the options ask for it (TibSun intro.cpp; in RA2
// all this does is play a movie).
// @ref ?unknown_name_index_482e60@@YIHPBD@Z=00482e60
// @ref ?Play_Movie@@YIXHH_N00@Z=005a07f0
// @ref ??_C@_05KMPM@INTRO?$AA@=007dbc90
#include "shared/special.hpp"
#include "shared/movie_list.hpp"
#include "shared/play_movie.hpp"

void Choose_Side()
{
    if (unknown_special_a40920.IsFromInstall) {
        Play_Movie(unknown_name_index_482e60("INTRO"), -1, false, true, true);
    }
}
