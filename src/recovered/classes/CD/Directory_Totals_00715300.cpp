// Directory_Totals_00715300 (0x00715300): walks a FindFirstFile pattern ("X:\dir\*") recursively, counting
// subdirectories (skipping "." and ".."), files and the low 32 bits of the file sizes. Caller and purpose unconfirmed.
#include "shared/win32_find.hpp"
#include "shared/crt_string.hpp"
#include "shared/crt_tokens.hpp"
// @ref __imp__FindFirstFileA@8=0079a1fc
// @ref __imp__FindNextFileA@8=0079a200
// @ref __imp__FindClose@4=0079a2f8
// @ref __stricmp=00781f20
// @ref ??_C@_01PJCK@?4?$AA@=007dbe44
// @ref ??_C@_02OOND@?4?4?$AA@=007f9bd0
// @ref ??_C@_02HMIE@?2?$CK?$AA@=007f9bcc

void __fastcall Directory_Totals_00715300(LPCSTR path,int *dirs,int *files,int *bytes)
{
    WIN32_FIND_DATA data;
    char sub[260];
    HANDLE handle=FindFirstFileA(path,&data);
    if (handle==INVALID_HANDLE_VALUE) return;
    do {
        if (data.dwFileAttributes & 0x10) {
            if (_stricmp(data.cFileName,".") && _stricmp(data.cFileName,"..")) {
                ++*dirs;
                strcpy(sub,path);
                sub[strlen(sub)-1]=0;
                strcat(sub,data.cFileName);
                strcat(sub,"\\*");
                Directory_Totals_00715300(sub,dirs,files,bytes);
            }
        } else {
            ++*files;
            *bytes+=data.nFileSizeLow;
        }
    } while (FindNextFileA(handle,&data));
    FindClose(handle);
}
