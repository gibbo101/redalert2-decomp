#include "shared/directdraw.hpp"
#include "shared/crt_memory.hpp"
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
unsigned int __cdecl Get_DirectDraw_Capabilities_00495fc0()
{
    char error[80];
    DDCAPS caps;
    if (!DirectDrawObject) return 0;
    memset(&caps,0,sizeof(caps));
    caps.dwSize=sizeof(caps);
    HRESULT result=DirectDrawObject->GetCaps(&caps,0);
    if (result!=0) {
        if (direct_draw_error_handler_008523ec) direct_draw_error_handler_008523ec(result);
        else {
            sprintf(error,direct_draw_error_format_007d59a8,result);
            MessageBoxA(MainWindow,error,direct_draw_error_title_007d599c,0x30);
        }
        return 0;
    }
    unsigned int flags=0;
    if (caps.dwCaps&0x40) flags=1;
    if (caps.dwCaps&0x80) flags|=2;
    if (caps.dwCaps&0x10000) flags|=4;
    if (caps.dwCaps&0x8000000) flags|=8;
    if (caps.dwCaps&0x4000000) flags|=16;
    if (caps.dwCaps&0x2000000) flags|=32;
    if (caps.dwCaps&0x200) flags|=64;
    return flags;
}
