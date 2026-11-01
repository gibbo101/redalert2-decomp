// MovieHandle *__fastcall Create_Movie_Handle(char const *name, Surface *surface, Rect const *area) (0x005A1D30)
// Opens the movie file found for name as a Bink or VQA movie playing onto
// surface (in area, or the whole surface).
// @ref ??_C@_04LMEE@?4bik?$AA@=007e329c
// @ref ??_C@_0BH@CNON@Play_Movie?$CI?$CJ?5as?5Bink?$CB?6?$AA@=007e3284
// @ref ?Find_Movie_File@@YI_NPBDPADH@Z=005a1bb0
// @ref _strrchr=00781ff0
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ??0BinkClass@@QAE@PBDPAVSurface@@@Z=0042fea0
// @ref ?VQA_Unknown_005A1010@@YIPAVVQAMovie@@PBDPAVSurface@@VRect@@2H_N@Z=005a1010
#include "shared/movie.hpp"
#include "shared/crt_string.hpp"
#include "shared/debug_printf.hpp"

extern "C" char *__cdecl strrchr(char const *string, int character);
extern "C" int __cdecl _stricmp(char const *string1, char const *string2);
VQAMovie *__fastcall VQA_Unknown_005A1010(char const *filename, Surface *surface, Rect unknown1, Rect area,
                                          int unknown2, bool unknown3);   // 0x005A1010

MovieHandle *__fastcall Create_Movie_Handle(char const *name, Surface *surface, Rect const *area)
{
    char filename[200];

    if (!surface || !Find_Movie_File(name, filename, 1)) {
        return 0;
    }

    Rect rect;
    if (area) {
        rect = *area;
    } else {
        rect = surface->Get_Rect();
    }

    char *extension = strrchr(filename, '.');
    if (extension && !_stricmp(extension, ".bik")) {
        Debug_Printf("Play_Movie() as Bink!\n");
        BinkClass *bink = new BinkClass(filename, surface);
        return new BinkMovieHandle(bink);
    }

    VQAMovie *movie = VQA_Unknown_005A1010(filename, surface, Rect(0, 0, 0, 0), rect, 0xFF, 0);
    if (!movie) {
        return 0;
    }
    return new VQMovieHandle(movie);
}
