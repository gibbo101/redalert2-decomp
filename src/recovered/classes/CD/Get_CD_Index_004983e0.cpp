#include "shared/cd_file_class.hpp"
#include "shared/cd_timer.hpp"
#include "shared/system_timer.hpp"
#include "shared/win32_api.hpp"
WIN32_IMPORT int __cdecl wsprintfA(char *out,char const *format,...);
WIN32_IMPORT BOOL WINAPI GetVolumeInformationA(char const *root,char *name,DWORD size,DWORD *serial,DWORD *max_component,DWORD *flags,char *filesystem,DWORD filesystem_size);
extern "C" int __cdecl sprintf(char *out,char const *format,...);
extern "C" int __cdecl _stricmp(char const *first,char const *second);
// @ref _sprintf=007820f4
// @ref __stricmp=00781f20
// @ref ??BSystemTimerClass@@QBEJXZ=0069a430
// @ref ??_C@_04CHBD@?$CFc?3?2?$AA@=007d239c
// @ref ??_C@_04FIJC@RA?$CFd?$AA@=007d5c68
// @ref ??_C@_0N@KIKC@?$CFc?3?2RA?$CFd?4dsk?$AA@=007d5c58
// Queries RA1..RA8 volume labels and verifies the corresponding RA<n>.dsk file.
// Format literals are independently checked against the verified target.
int __fastcall Get_CD_Index(int drive,int timeout)
{
    CDTimerClass<SystemTimerClass> timer;
    timer = CDTimerClass<SystemTimerClass>(timeout);
    char path[128];
    char volume[128];
    char expected[32];
    DWORD maximum_component;
    DWORD flags;
    int letter = drive + 'A';
    wsprintfA(path,"%c:\\",letter);
    while (!GetVolumeInformationA(path,volume,127,0,&maximum_component,&flags,0,0)) {
        if (timer.Value() == 0 || GetLastError() != 21) return -1;
        wsprintfA(path,"%c:\\",letter);
    }
    int index=-1;
    for (int candidate=0;candidate<8;++candidate) {
        sprintf(expected,"RA%d",candidate+1);
        if (_stricmp(expected,volume) == 0) {
            index=candidate;
            break;
        }
    }
    if (index > -1) {
        int retries=0;
        for (;;) {
            wsprintfA(path,"%c:\\RA%d.dsk",letter,index+1);
            HANDLE file=CreateFileA(path,GENERIC_READ,FILE_SHARE_READ,0,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);
            if (file != INVALID_HANDLE_VALUE) {
                CloseHandle(file);
                return index;
            }
            if (++retries >= 2) return -1;
        }
    }
    return -1;
}
