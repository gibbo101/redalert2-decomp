#include "shared/dsurface.hpp"
#include "shared/debug_printf.hpp"
extern bool direct_draw_overlap_enabled_007d6295;
extern char const color_fill_test_log_007d5a44[];
extern char const color_fill_enabled_007d5a40[];
extern char const color_fill_disabled_007d5a38[];
extern char const color_fill_result_format_007d5a34[];
extern char const overlap_test_log_007d5a0c[];
extern char const overlap_failed_007d5a00[];
extern char const overlap_passed_007d59fc[];
void __cdecl Video_Debug_Log_00496460(char const *format,...);
// @ref ?direct_draw_overlap_enabled_007d6295@@=007d6295
// @ref ?unknown_flag_7d6294@@=007d6294
// @ref ?color_fill_test_log_007d5a44@@=007d5a44
// @ref ?color_fill_enabled_007d5a40@@=007d5a40
// @ref ?color_fill_disabled_007d5a38@@=007d5a38
// @ref ?color_fill_result_format_007d5a34@@=007d5a34
// @ref ?overlap_test_log_007d5a0c@@=007d5a0c
// @ref ?overlap_failed_007d5a00@@=007d5a00
// @ref ?overlap_passed_007d59fc@@=007d59fc
// @ref ?Debug_Printf@@=004068f0
// @ref ?Video_Debug_Log_00496460@@=00496460
// @ref ??0DSurface@@QAE@HHE@Z=004aa4a0
// @ref ??1DSurface@@UAE@XZ=004aa5a0
// @ref ?Fill@XSurface@@UAE_NH@Z=00774e20
// @ref ?Get_Pixel@XSurface@@UAEHABUPoint2D@@@Z=007741d0
// @ref ?Put_Pixel@XSurface@@UAE_NABUPoint2D@@H@Z=00774220
void __fastcall Probe_DirectDraw_Rendering_004957e0()
{
    DSurface surface(64,64,false);
    Debug_Printf(color_fill_test_log_007d5a44);
    unknown_flag_7d6294=true;
    surface.Fill(0);
    if (surface.Get_Pixel(Point2D(5,5))!=0) {
        unknown_flag_7d6294=false;
    } else {
        surface.Fill(1);
        if (surface.Get_Pixel(Point2D(5,5))!=1) unknown_flag_7d6294=false;
    }
    Video_Debug_Log_00496460(color_fill_result_format_007d5a34,
        unknown_flag_7d6294?color_fill_enabled_007d5a40:color_fill_disabled_007d5a38);
    Debug_Printf(overlap_test_log_007d5a0c);
    direct_draw_overlap_enabled_007d6295=true;
    surface.Fill(0);
    surface.Put_Pixel(Point2D(0,0),255);
    surface.Copy_From(Rect(0,1,64,63),surface,Rect(0,0,64,63),false,false);
    if (surface.Get_Pixel(Point2D(0,5))!=0) {
        Video_Debug_Log_00496460(overlap_failed_007d5a00);
        direct_draw_overlap_enabled_007d6295=false;
        return;
    }
    Video_Debug_Log_00496460(overlap_passed_007d59fc);
}
