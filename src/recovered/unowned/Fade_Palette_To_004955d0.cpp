// @ref ?unknown_palette_00851cc8@@3VPaletteClass@@A=00851cc8
// @ref ??BSystemTimerClass@@QBEJXZ=0069a430
// @ref ?unknown_surface_839950@@3PAVSurface@@A=00839950
// @ref ?Set@PaletteClass@@QAEXXZ=00496120
// @ref ?Adjust@PaletteClass@@QAEXHABV1@@Z=006030d0
#define DIRECTDRAW_DECLARE_MODE_METHODS
#define RA2_PALETTE_CONSTRUCTORS
#define PALETTE_DECLARE_MEMBERS
#include "shared/palette_state.hpp"
#include "shared/cd_timer.hpp"
#include "shared/system_timer.hpp"
#include "shared/surface.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/crt_memory.hpp"
void __fastcall Fade_Palette_To(PaletteClass const &target, int time, void (*callback)())
{
    if (unknown_surface_839950->Bytes_Per_Pixel() != 1) return;
    CDTimerClass<SystemTimerClass> timer = time;
    PaletteClass original;
    memcpy(&original, &unknown_palette_00851cc8, sizeof(PaletteClass));
    PaletteClass goal = target;
    while (timer) {
        PaletteClass palette = original;
        int ratio = ((time - timer) * 256) / time;
        if (ratio >= 255) ratio = 255;
        palette.Adjust(ratio, goal);
        int holdtime = timer;
        palette.Set();
        if (callback) callback();
        while (timer == holdtime && holdtime != 0) {
            if (callback) callback();
        }
    }
    goal.Set();
}
