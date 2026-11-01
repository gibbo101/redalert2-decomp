// UnknownScore_005AAA20::UnknownScore_005AAA20() (0x005AAA20): clears the screen's statics.
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#define VECTOR_IMPLEMENT_VECTOR_DESTRUCTOR
#include "shared/house.hpp"
#include "shared/debug_printf.hpp"
#include "shared/session_state.hpp"
#include "shared/id_source.hpp"
#include "shared/ms_message_box.hpp"
#include "shared/color_scheme.hpp"
#include "shared/string_table.hpp"
#include "shared/campaign_score.hpp"
#include "shared/theme.hpp"
#include "shared/win32_window.hpp"
#include "shared/movie_globals.hpp"
#include "shared/crt_string.hpp"
#include "shared/dsurface.hpp"
#include "shared/mpscore.hpp"

extern "C" wchar_t *__cdecl wcscpy(wchar_t *destination, wchar_t const *source);
void __fastcall Unknown_6F3CD0(Surface *surface, Rect const &window);
void __fastcall Unknown_Rect_Shrink_006F1B30(Rect *rect, int x, int y);

UnknownScore_005AAA20::UnknownScore_005AAA20()
{
    unknown_score_a71684 = 0;
    unknown_score_a71688 = 0;
    memset(unknown_sorted_scores_a715f0, 0, sizeof(unknown_sorted_scores_a715f0));
}
// @ref ?unknown_score_a71684@@3HA=00a71684
// @ref ?unknown_score_a71688@@3HA=00a71688
