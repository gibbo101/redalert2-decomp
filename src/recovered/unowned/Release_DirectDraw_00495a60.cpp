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
void __cdecl Release_DirectDraw_00495a60()
{
    char error[80];
    if (DirectDrawObject) {
        unsigned long result = DirectDrawObject->Release();
        if (result != 0) {
            if (direct_draw_error_handler_008523ec) direct_draw_error_handler_008523ec(result);
            else {
                sprintf(error,direct_draw_error_format_007d59a8,result);
                MessageBoxA(MainWindow,error,direct_draw_error_title_007d599c,0x30);
            }
        }
        DirectDrawObject = 0;
    }
}
