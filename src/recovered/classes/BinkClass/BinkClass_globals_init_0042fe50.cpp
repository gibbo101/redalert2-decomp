// Dynamic initializer of unknown_empty_rect (0x0042FE50, _$E), the file-local
// empty Rect from shared/shape_file.hpp (0x0084E9B0 in this unit).
#include "shared/movie.hpp"
#include "shared/shape_file.hpp"
// @ref _unknown_empty_rect=0084e9b0
// @ref ?unknown_check_406f30@@YAHXZ=00406f30
// @ref ?unknown_directsound_40a6c0@@YAPAXXZ=0040a6c0
// @ref ?unknown_volume_a40b48@@3MA=00a40b48
// @ref ?unknown_volume_84e9a8@@3MA=0084e9a8
// @ref ?unknown_create_companion_69b190@@YIPAVVQAMovieCompanion@@PBD@Z=0069b190
// @ref ?unknown_surface_839950@@3PAVSurface@@A=00839950
// @ref ?unknown_surface_839954@@3PAVSurface@@A=00839954
// @ref ?MainWindow@@3PAUHWND__@@A=00b263d8
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref __real@4@400e8000000000000000=0079c780
// Bink SDK imports (IAT, manifests/imports.json):
// @ref __imp__BinkSetSoundSystem@8=0079a584
// @ref __imp__BinkOpenDirectSound@4=0079a588
// @ref __imp__BinkGetError@0=0079a58c
// @ref __imp__BinkOpen@8=0079a590
// @ref __imp__BinkSetVolume@8=0079a594
// @ref __imp__BinkClose@4=0079a598
// @ref __imp__BinkDDSurfaceType@4=0079a59c
// @ref __imp__BinkGoto@12=0079a5a0
// @ref __imp__BinkPause@8=0079a5a4
// @ref __imp__BinkNextFrame@4=0079a5a8
// @ref __imp__BinkCopyToBuffer@28=0079a5ac
// @ref __imp__BinkDoFrame@4=0079a5b0
// @ref __imp__BinkWait@4=0079a5b4

// Intersect (kept copy 0x0041FDF0) is an inline header function in the
// original; defined here for this unit until shared/rect.hpp carries it
// (as in MSAnim.cpp).
inline Rect __fastcall Intersect(Rect const &rect1, Rect const &rect2, int *x, int *y)
{
    Rect empty(0, 0, 0, 0);
    Rect result = rect2;
    if (!rect1.Is_Valid() || !rect2.Is_Valid()) {
        return empty;
    }
    if (result.X < rect1.X) {
        result.Width += result.X - rect1.X;
        result.X = rect1.X;
    }
    if (result.Width < 1) {
        return empty;
    }
    if (result.Y < rect1.Y) {
        result.Height += result.Y - rect1.Y;
        result.Y = rect1.Y;
    }
    if (result.Height < 1) {
        return empty;
    }
    if (result.X + result.Width > rect1.X + rect1.Width) {
        result.Width = rect1.X - result.X + rect1.Width;
    }
    if (result.Width < 1) {
        return empty;
    }
    if (result.Y + result.Height > rect1.Y + rect1.Height) {
        result.Height = rect1.Y + rect1.Height - result.Y;
    }
    if (result.Height < 1) {
        return empty;
    }
    if (x != 0) {
        *x += rect2.X - result.X;
    }
    if (y != 0) {
        *y += rect2.Y - result.Y;
    }
    return result;
}


