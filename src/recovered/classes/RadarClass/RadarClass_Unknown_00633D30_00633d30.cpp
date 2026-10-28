// void RadarClass::Unknown_00633D30() (0x00633D30)
// The mode-3 (movie) update: redraws the frame when a full radar redraw is
// due, steps the first queued movie and, when it is finished, deletes it and
// starts the next one; with none left the radar returns to its previous mode
// (+0x14B0). Follows the movie's flag at +0x04 through +0x14B8.
#include "shared/radar.hpp"
#include "shared/rules.hpp"
#include "shared/movie.hpp"
#include "shared/palette.hpp"
// @ref ??_C@_0BE@BCE@Radar?3?5Next?5movie?4?6?$AA@=007ee368
// @ref ??_C@_0BE@PJHM@Radar?3?5Movie?5done?4?6?$AA@=007ee354
// @ref ??_C@_0BL@KIPA@Radar?3?5Movie?5full?5redrawn?6?$AA@=007ee37c
// @ref ?queued_movies_00af8fd8@@3V?$DynamicVectorClass@PAVMovieHandle@@@@A=00af8fd8
// @ref ?Speech_Is_Playing@@YA_NXZ=00715e20
// @ref ?Unknown_005A0AC0@@YAXXZ=005a0ac0
// @ref ?Unknown_0065C1F0@@YIXH@Z=0065c1f0
// @ref ?Unknown_0065C310@@YAXXZ=0065c310
// @ref ?unknown_set_frame_rate_0053d820@@YIXH@Z=0053d820

void RadarClass::Unknown_00633D30()
{
    MovieHandle *movie = 0;
    bool flag = false;
    bool playing = queued_movies_00af8fd8.Count() > 0;
    if (!unknown_14b9 && playing) {
        Speech_Is_Playing();
    }
    if (unknown_14d6 == true && !unknown_14b9) {
        CC_Draw_Shape(unknown_surface_839948, unknown_drawer_8323cc, (ShapeFileStruct const *)unknown_shape_ab64a0, 32,
                      Point2D(unknown_11e0, unknown_11e8), unknown_surface_839948->Get_Rect(), 0, 0, 0, 0, 1000, 0, 0,
                      Point2D(0, 0));
        unknown_1208 = Rect(unknown_11e0, unknown_11e8, unknown_int_7add80, 110);
        Debug_Printf("Radar: Movie full redrawn\n");
    }
    bool done;
    if (playing && queued_movies_00af8fd8.Count() > 0 && (movie = queued_movies_00af8fd8[0]) != 0) {
        if (movie->Unknown_Slot1() == true) {
            unknown_1208 = Rect(unknown_11e0, unknown_11e8, unknown_int_7add80, 110);
        }
        done = movie->Is_Finished();
        flag = movie->unknown_04;
    } else if (playing) {
        done = true;
    } else {
        done = false;
    }
    if (done == true) {
        if (movie != 0) {
            queued_movies_00af8fd8.Delete(movie);
            delete movie;
        }
        playing = queued_movies_00af8fd8.Count() != 0;
        if (playing) {
            Debug_Printf("Radar: Next movie.\n");
            unknown_14bc.Unknown_00406070();
            unknown_14bc.Unknown_00406100(Voc_Play(Rules->unknown_618, 1.0f, 0x2000, 0), 0);
            unknown_14a8 = 4;
            unknown_14f8 = 25;
        }
    }
    unknown_14d5 = false;
    if (!playing) {
        Debug_Printf("Radar: Movie done.\n");
        unknown_14a8 = 5;
        Unknown_00633000(unknown_14b0, false);
        Unknown_005A0AC0();
        flag = playing;
        unknown_14bc.Unknown_00406070();
        unknown_14bc.Unknown_00406100(Voc_Play(Rules->MovieOff, 1.0f, 0x2000, 0), 0);
        unknown_set_frame_rate_0053d820(Rules->DetailMinFrameRateNormal);
        unknown_14d5 = true;
    }
    unknown_14b9 = !done;
    if (unknown_14b8 != flag) {
        if (flag) {
            Unknown_0065C1F0(0);
            unknown_14b8 = true;
        } else {
            Unknown_0065C310();
            unknown_14b8 = false;
        }
    }
}
