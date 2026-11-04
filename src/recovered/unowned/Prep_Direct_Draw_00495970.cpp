// @ref ?DirectDrawObject@@3PAUIDirectDraw@@A=008523cc
// @ref ?direct_draw_error_handler_008523ec@@=008523ec
// @ref ?MainWindow@@=00b263d8
// @ref ?direct_draw_error_format_007d59a8@@=007d59a8
// @ref ?direct_draw_error_title_007d599c@@=007d599c
// @ref _sprintf=007820f4
// @ref _DirectDrawCreate@12=00781bd8
// @ref ?Debug_Printf@@=004068f0
// @ref ?unknown_flag_851cb0@@3_NA=00851cb0
// @ref ?direct_draw_prep_log_007d5a8c@@=007d5a8c
// @ref ?direct_draw_create_failed_007d5a70@@=007d5a70
#include "shared/ddraw_result.hpp"
#include "shared/debug_printf.hpp"
extern IDirectDraw *DirectDrawObject;
extern bool unknown_flag_851cb0;
extern char const direct_draw_prep_log_007d5a8c[];
extern char const direct_draw_create_failed_007d5a70[];
void __cdecl Prep_Direct_Draw()
{
    Debug_Printf(direct_draw_prep_log_007d5a8c);
    if (DirectDrawObject == 0) {
        HRESULT result = DirectDrawCreate(0, &DirectDrawObject, 0);
        Process_DD_Result(result, false);
        if (result == DD_OK) {
            if (unknown_flag_851cb0) result = DirectDrawObject->SetCooperativeLevel(MainWindow, 8);
            else result = DirectDrawObject->SetCooperativeLevel(MainWindow, 0x11);
            Process_DD_Result(result, false);
        } else {
            Debug_Printf(direct_draw_create_failed_007d5a70);
        }
    }
}
