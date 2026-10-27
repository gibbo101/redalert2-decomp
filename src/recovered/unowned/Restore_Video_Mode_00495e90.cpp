#include "shared/directdraw.hpp"
#include "shared/win32_api.hpp"
extern IDirectDraw *DirectDrawObject;
extern void (__fastcall *direct_draw_error_handler_008523ec)(HRESULT result);
extern HWND MainWindow;
extern char const direct_draw_error_format_007d59a8[];
extern char const direct_draw_error_title_007d599c[];
extern "C" int __cdecl sprintf(char *buffer, char const *format, ...);
WIN32_IMPORT int WINAPI MessageBoxA(HWND window, char const *text, char const *caption, UINT type);
// @ref ?DirectDrawObject@@=008523cc
// @ref ?direct_draw_error_handler_008523ec@@=008523ec
// @ref ?MainWindow@@=00b263d8
// @ref ?direct_draw_error_format_007d59a8@@=007d59a8
// @ref ?direct_draw_error_title_007d599c@@=007d599c
// @ref _sprintf=007820f4
extern int direct_draw_width_008523e0,direct_draw_height_008523e4,direct_draw_depth_008523e8;
// @ref ?direct_draw_width_008523e0@@=008523e0
// @ref ?direct_draw_height_008523e4@@=008523e4
// @ref ?direct_draw_depth_008523e8@@=008523e8
void __cdecl Restore_Video_Mode_00495e90()
{
    char error[80];
    if (DirectDrawObject) {
        HRESULT result=DirectDrawObject->RestoreDisplayMode();
        if (result!=0) {
            if (direct_draw_error_handler_008523ec) direct_draw_error_handler_008523ec(result);
            else {
                sprintf(error,direct_draw_error_format_007d59a8,result);
                MessageBoxA(MainWindow,error,direct_draw_error_title_007d599c,0x30);
            }
        }
        direct_draw_width_008523e0=0;
        direct_draw_height_008523e4=0;
        direct_draw_depth_008523e8=0;
        unsigned long releaseCount=DirectDrawObject->Release();
        if (releaseCount!=0) {
            if (direct_draw_error_handler_008523ec) direct_draw_error_handler_008523ec(releaseCount);
            else {
                sprintf(error,direct_draw_error_format_007d59a8,releaseCount);
                MessageBoxA(MainWindow,error,direct_draw_error_title_007d599c,0x30);
            }
        }
        DirectDrawObject=0;
    }
}
