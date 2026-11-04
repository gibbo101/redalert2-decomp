// @ref ?DirectDrawObject@@3PAUIDirectDraw@@A=008523cc
// @ref ?direct_draw_error_handler_008523ec@@=008523ec
// @ref ?MainWindow@@=00b263d8
// @ref ?direct_draw_error_format_007d59a8@@=007d59a8
// @ref ?direct_draw_error_title_007d599c@@=007d599c
// @ref _sprintf=007820f4
// @ref ?Debug_Printf@@=004068f0
// @ref ?unknown_palette_00851fc8@@3PAUIDirectDrawPalette@@A=00851fc8
// @ref ?unknown_palette_entries_00851fcc@@3PAUPALETTEENTRY@@A=00851fcc
// @ref ?direct_draw_width_008523e0@@=008523e0
// @ref ?direct_draw_height_008523e4@@=008523e4
// @ref ?direct_draw_depth_008523e8@@=008523e8
// @ref ?set_display_mode_log_007d5b7c@@=007d5b7c
// @ref ?set_display_mode_failed_007d5b64@@=007d5b64
// @ref ?create_palette_log_007d5b54@@=007d5b54
// @ref ?create_palette_failed_007d5b3c@@=007d5b3c
// @ref ?display_mode_set_log_007d5b28@@=007d5b28
// @ref ?Probe_DirectDraw_Rendering_004957e0@@=004957e0
#include "shared/ddraw_result.hpp"
#include "shared/debug_printf.hpp"
#include "shared/palette_state.hpp"
extern IDirectDraw *DirectDrawObject;
extern int direct_draw_width_008523e0, direct_draw_height_008523e4, direct_draw_depth_008523e8;
extern char const set_display_mode_log_007d5b7c[];
extern char const set_display_mode_failed_007d5b64[];
extern char const create_palette_log_007d5b54[];
extern char const create_palette_failed_007d5b3c[];
extern char const display_mode_set_log_007d5b28[];
void __fastcall Probe_DirectDraw_Rendering_004957e0();
void __cdecl Prep_Direct_Draw();
bool __fastcall Set_Video_Mode(HWND, int w, int h, int bits_per_pixel)
{
    HRESULT result;
    Prep_Direct_Draw();
    Debug_Printf(set_display_mode_log_007d5b7c, w, h, bits_per_pixel);
    result = DirectDrawObject->SetDisplayMode(w, h, bits_per_pixel);
    if (result != DD_OK) {
        Debug_Printf(set_display_mode_failed_007d5b64);
        return false;
    }
    direct_draw_width_008523e0 = w;
    direct_draw_height_008523e4 = h;
    direct_draw_depth_008523e8 = bits_per_pixel;
    if (bits_per_pixel == 8) {
        Debug_Printf(create_palette_log_007d5b54);
        result = DirectDrawObject->CreatePalette(0x44, unknown_palette_entries_00851fcc, (void **)&unknown_palette_00851fc8, 0);
        Process_DD_Result(result, false);
        if (result != DD_OK) {
            Debug_Printf(create_palette_failed_007d5b3c);
            return false;
        }
    }
    Probe_DirectDraw_Rendering_004957e0();
    Debug_Printf(display_mode_set_log_007d5b28);
    return true;
}
