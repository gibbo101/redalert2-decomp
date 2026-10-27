#include "shared/directdraw.hpp"
extern IDirectDraw *DirectDrawObject;
extern char const video_memory_log_007d5b98[];
extern "C" int __cdecl sprintf(char *buffer, char const *format, ...);
// @ref ?DirectDrawObject@@=008523cc
// @ref ?video_memory_log_007d5b98@@=007d5b98
// @ref _sprintf=007820f4
DWORD __cdecl Get_Free_Video_Memory_00495f60()
{
    DDCAPS caps;
    char buffer[256];
    if (DirectDrawObject) {
        caps.dwSize=sizeof(caps);
        if (DirectDrawObject->GetCaps(&caps,0)==0) {
            sprintf(buffer,video_memory_log_007d5b98,caps.dwVidMemFree);
            return caps.dwVidMemFree;
        }
    }
    return 0;
}
