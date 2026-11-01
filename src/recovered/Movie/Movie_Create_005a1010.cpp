// VQAMovie *__fastcall Movie_Create(char const *name, Surface *surface, Rect source, Rect dest, int volume,
// bool fullscreen) (0x005A1010)
// TibSun Movie_Create: a new VQA movie for name drawing onto surface, its player locking the movie's frame
// surface (fullscreen: Movie_Blit_To_Screen_Hidden copies each frame to the screen); an empty source is the
// whole movie, an empty dest the movie centred on surface, both clipped. The subtitle companion is created
// from the name. Null when the file is missing or the movie does not open.
#include "shared/movie.hpp"
#include "shared/hicolor.hpp"
#include "shared/sound_available.hpp"
#include "shared/rect_intersect.hpp"
// @ref ??2@YAPAXI@Z=00782017
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ??0CCFileClass@@QAE@PBD@Z=00468f50
// @ref ??1Buffer@@QAE@XZ=00438410
// @ref ??1BufferIOFileClass@@UAE@XZ=0042f350
// @ref ??_7CCFileClass@@6B@=0079a6a0
// @ref ??_7CDFileClass@@6B@=0079a658
// @ref ??0Rect@@QAE@HHHH@Z=0042bcd0
// @ref ?Intersect@@YI?AVRect@@ABV1@0PAH1@Z=0041fdf0
// @ref ?unknown_check_406f30@@YAHXZ=00406f30
// @ref ?VQA_Unknown_0071DB60@@YIXH@Z=0071db60
// @ref ?VQA_Unknown_0071DBA0@@YI_NH@Z=0071dba0
// @ref ?MovieInt1@@3HA=00a710b4
// @ref ?Movie_Lock_Surface@@YIHXZ=005a0dc0
// @ref ?Movie_Unlock_Surface@@YAXXZ=005a0e20
// @ref ?Movie_Blit_To_Screen_Hidden@@YAXXZ=005a0ec0
// @ref ?Get_Unknown_7d6290@@YAHXZ=004abb90
// @ref ?unknown_create_companion_69b190@@YIPAVVQAMovieCompanion@@PBD@Z=0069b190

int MovieInt1;      // 0x00A710B4 (TibSun MovieInt1: 1 adds player flag 2)

int __fastcall Movie_Lock_Surface();
// The VQAClass constructor takes the lock callback as int (*)(); this one is __fastcall (cast below).
void Movie_Unlock_Surface();
void Movie_Blit_To_Screen_Hidden();

// TibSun rect.h's two-argument Intersect, a wrapper over the four-argument form (shared/rect.hpp declares that one
// with default x/y, so the wrapper takes its own name here). The wrapper puts the inline Intersect one level deeper:
// the first call stays out of line (0x0041FDF0), the second is expanded.
inline Rect Intersect_Rects(Rect const &rect1, Rect const &rect2)
{
    return Intersect(rect1, rect2, (int *)0, (int *)0);
}

VQAMovie *__fastcall VQA_Unknown_005A1010(char const *name, Surface *surface, Rect source, Rect dest, int volume,
                                          bool fullscreen)
{
    void (*callback)() = 0;
    VQAMovie *movie = new VQAMovie;
    if (movie != 0) {
        if (!CCFileClass(name).Is_Available()) {
            return 0;
        }
        int flags = 0;

        if (!unknown_check_406f30()) {
            VQA_Unknown_0071DB60(3);
        }

        if (VQA_Unknown_0071DBA0(0)) {
            flags |= 1;
        }

        if (MovieInt1 == 1) {
            flags |= 2;
        }

        if (fullscreen == true) {
            callback = Movie_Blit_To_Screen_Hidden;
        }

        movie->Player = new VQAClass(name, flags, (int (*)())Movie_Lock_Surface, Movie_Unlock_Surface, callback,
                                     -1, -1);
        if (movie->Player == 0) {
            delete movie;
            return 0;
        }

        movie->Player->Unknown_0071CBC0(volume);

        if (!movie->Player->Unknown_0071CB30()) {
            delete movie;
            return 0;
        }

        int width = movie->Player->Unknown_0071D300();
        int height = movie->Player->Unknown_0071D310();
        int cmode = movie->Player->Unknown_0071D230();

        if (cmode == 4) {
            cmode = 1;
        }

        if (source == Rect(0, 0, 0, 0)) {
            source = Rect(0, 0, width, height);
        }

        if (dest == Rect(0, 0, 0, 0)) {
            dest = Rect((surface->Get_Width() - width) / 2, (surface->Get_Height() - height) / 2, width, height);
        }

        Rect irect1(0, 0, width, height);
        Rect irect2(0, 0, surface->Get_Width(), surface->Get_Height());

        movie->Source = Intersect_Rects(source, irect1);
        movie->Dest = Intersect_Rects(dest, irect2);

        if (cmode == 1 || cmode == 4) {
            movie->Player->Unknown_0071D2B0(Get_Unknown_7d6290());
        }

        movie->FrameSurface = surface;
        movie->Player->Unknown_0071D240(0, surface->Stride() / surface->Bytes_Per_Pixel(), surface->Get_Height(),
                                        0, 0);
        movie->Companion = unknown_create_companion_69b190(name);
        if (movie->Companion != 0) {
            movie->Player->Companion = movie->Companion;
        }
        movie->Playing = true;
        return movie;
    }
    return 0;
}
