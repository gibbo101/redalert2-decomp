// void UnknownScore_0069A640::Presentation_0069A650() (0x0069A650)
// Loads the score art, clears the screen behind the dialog, runs the score
// dialog 0x103 (procedure 0x0069A7D0) and clears the screen again.
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref ?Unknown_Load_Art_Once_006F2710@@YIXH@Z=006f2710
// @ref ?Unknown_Free_Art_Flagged_006F2750@@YAXXZ=006f2750
// @ref ?unknown_dialog_box_5eab60@@YIHHP6GHPAUHWND__@@IIJ@Z_N@Z=005eab60
// @ref ?Unknown_6F3BF0@@YIXPAVSurface@@ABVRect@@@Z=006f3bf0
// @ref ?Unknown_004E0C90@@YIX_NPAVSurface@@H@Z=004e0c90
// @ref ?Score_Dialog_Proc_0069A7D0@@YGHPAUHWND__@@IIJ@Z=0069a7d0
#include "shared/id_source.hpp"
#include "shared/campaign_score.hpp"
#include "shared/movie_globals.hpp"
#include "shared/rect.hpp"
#include "shared/unknown_globals.hpp"

// Clears the screen area behind the score dialog (0x006F3BF0; hypothesis).
void __fastcall Unknown_6F3BF0(Surface *surface, Rect const &window);
// The score dialog's procedure (0x0069A7D0; not recovered).
int __stdcall Score_Dialog_Proc_0069A7D0(HWND__ *dialog, unsigned int message, unsigned int wparam, long lparam);

void UnknownScore_0069A640::Presentation_0069A650()
{
    Unknown_Load_Art_Once_006F2710(unknown_id_source_a3d290->unknown_2239 == false);
    Rect rect(0, 0, unknown_8523e0, unknown_8523e4);
    Unknown_6F3BF0(unknown_surface_839954, rect);
    Unknown_004E0C90(true, unknown_surface_839954, 0);
    unknown_dialog_box_5eab60(0x103, Score_Dialog_Proc_0069A7D0, 0);
    Unknown_6F3BF0(unknown_surface_839954, rect);
    Unknown_004E0C90(true, unknown_surface_839954, 0);
    Unknown_Free_Art_Flagged_006F2750();
}
