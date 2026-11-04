// @ref ?DirectDrawObject@@3PAUIDirectDraw@@A=008523cc
// @ref ?direct_draw_error_handler_008523ec@@=008523ec
// @ref ?MainWindow@@=00b263d8
// @ref ?direct_draw_error_format_007d59a8@@=007d59a8
// @ref ?direct_draw_error_title_007d599c@@=007d599c
// @ref _sprintf=007820f4
// @ref _DirectDrawCreate@12=00781bd8
// @ref ?Debug_Printf@@=004068f0
// @ref ?video_memory_actual_log_007d5af8@@=007d5af8
// @ref ?video_memory_display_log_007d5ac8@@=007d5ac8
// @ref ?video_memory_adjusted_log_007d5aa0@@=007d5aa0
#include "shared/ddraw_result.hpp"
#include "shared/debug_printf.hpp"
#include "shared/crt_string.hpp"
extern IDirectDraw *DirectDrawObject;
extern char const video_memory_actual_log_007d5af8[];
extern char const video_memory_display_log_007d5ac8[];
extern char const video_memory_adjusted_log_007d5aa0[];
DWORD __cdecl Get_Video_Memory()
{
    HRESULT result;
    DDCAPS video_capabilities;
    DDSURFACEDESC desc;
    bool created = false;
    if (DirectDrawObject == 0) {
        result = DirectDrawCreate(0, &DirectDrawObject, 0);
        Process_DD_Result(result, false);
        if (result == DD_OK) {
            created = true;
        } else {
            DirectDrawObject = 0;
        }
    }
    DWORD video_memory = 0;
    if (DirectDrawObject) {
        video_capabilities.dwSize = sizeof(video_capabilities);
        if (DD_OK == DirectDrawObject->GetCaps(&video_capabilities, 0)) {
            video_memory = video_capabilities.dwVidMemTotal;
            Debug_Printf(video_memory_actual_log_007d5af8, video_memory, video_memory >> 20);
            memset(&desc, 0, sizeof(desc));
            desc.dwSize = sizeof(desc);
            if (DirectDrawObject->GetDisplayMode(&desc) == 0) {
                Debug_Printf(video_memory_display_log_007d5ac8, desc.dwWidth, desc.dwHeight, desc.ddpfPixelFormat.dwRGBBitCount, desc.lPitch);
                video_memory += desc.dwWidth * desc.dwHeight * (desc.ddpfPixelFormat.dwRGBBitCount >> 3);
            }
            video_memory += 512 * 256;
            video_memory &= 0xfff00000;
            Debug_Printf(video_memory_adjusted_log_007d5aa0, video_memory, video_memory >> 20);
        }
    }
    if (created) {
        if (DirectDrawObject != 0) {
            result = DirectDrawObject->Release();
            Process_DD_Result(result, false);
            DirectDrawObject = 0;
        }
    }
    return video_memory;
}
