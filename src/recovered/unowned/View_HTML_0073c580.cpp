#include "shared/wol_sink.hpp"
#include "shared/lobby.hpp"
#include "shared/win32_window.hpp"
#include "shared/crt_stdio.hpp"
#include "shared/crt_string.hpp"
struct _SECURITY_ATTRIBUTES;
struct _STARTUPINFOA {
    DWORD cb;
    char *lpReserved,*lpDesktop,*lpTitle;
    DWORD dwX,dwY,dwXSize,dwYSize,dwXCountChars,dwYCountChars,dwFillAttribute,dwFlags;
    unsigned short wShowWindow,cbReserved2;
    unsigned char *lpReserved2;
    HANDLE hStdInput,hStdOutput,hStdError;
};
struct _PROCESS_INFORMATION { HANDLE hProcess,hThread; DWORD dwProcessId,dwThreadId; };
WIN32_IMPORT HINSTANCE WINAPI FindExecutableA(char const *,char const *,char *);
WIN32_IMPORT BOOL WINAPI CreateProcessA(char const *,char *,_SECURITY_ATTRIBUTES *,_SECURITY_ATTRIBUTES *,BOOL,DWORD,void *,char const *,_STARTUPINFOA *,_PROCESS_INFORMATION *);
WIN32_IMPORT DWORD WINAPI WaitForInputIdle(HANDLE,DWORD);
WIN32_IMPORT BOOL WINAPI GetExitCodeProcess(HANDLE,DWORD *);
WIN32_IMPORT HWND WINAPI GetTopWindow(HWND);
WIN32_IMPORT HWND WINAPI GetForegroundWindow();
extern "C" char *__cdecl tmpnam(char *);
extern "C" int __cdecl _unlink(char const *);
extern char html_extension_007fd65c[],html_write_mode_007e09c0[],html_title_007fd640[];
extern char html_command_007fd60c[],html_launch_label_007fd618[],html_missing_label_007fd5fc[],wol_source_file_007fd62c[];
// @ref __imp__FindExecutableA@12=0079a380
// @ref __imp__CreateProcessA@40=0079a1a4
// @ref __imp__WaitForInputIdle@8=0079a410
// @ref __imp__GetExitCodeProcess@8=0079a180
// @ref __imp__GetTopWindow@4=0079a414
// @ref __imp__GetForegroundWindow@0=0079a418
// @ref _tmpnam=007856ad
// @ref __unlink=007856a2
// @ref ?html_extension_007fd65c@@3PADA=007fd65c
// @ref ?html_write_mode_007e09c0@@3PADA=007e09c0
// @ref ?html_title_007fd640@@3PADA=007fd640
// @ref ?html_command_007fd60c@@3PADA=007fd60c
// @ref ?html_launch_label_007fd618@@3PADA=007fd618
// @ref ?html_missing_label_007fd5fc@@3PADA=007fd5fc
// @ref ?wol_source_file_007fd62c@@3PADA=007fd62c
// @ref ?Unknown_0073e100@@YA_NXZ=0073e100
void __fastcall View_HTML_0073c580(char const *url,int no_ask)
{
    char filename[160];
    tmpnam(filename);
    strcat(filename,html_extension_007fd65c);
    _iobuf *file=fopen(filename,html_write_mode_007e09c0);
    fprintf(file,html_title_007fd640);
    fclose(file);
    char executable[261];
    int result=(int)FindExecutableA(filename,0,executable);
    _unlink(filename);
    if(result>32) {
        if(!no_ask && Popup_005c3230(StringTable::Load_String(html_launch_label_007fd618,0,wol_source_file_007fd62c,0x494),4,Unknown_0073c120,0)!=6) return;
        char command_line[270];
        sprintf(command_line,html_command_007fd60c,url);
        _STARTUPINFOA startup;
        memset(&startup,0,sizeof(startup));
        startup.cb=sizeof(startup);
        _PROCESS_INFORMATION process_info;
        if(CreateProcessA(executable,command_line,0,0,false,0,0,0,&startup,&process_info)) {
            HANDLE process=process_info.hProcess;
            if(process) {
            int done=0;
            Unknown_0073e100();
            WaitForInputIdle(process,5000);
            do {
                Unknown_0073e100();
                Sleep(500);
                DWORD exit_code;
                GetExitCodeProcess(process,&exit_code);
                if(exit_code!=0x103) done=1;
                if(unknown_flag_a40d28 || GetTopWindow(0)==MainWindow || GetForegroundWindow()==MainWindow) done=1;
                Unknown_0073e100();
            } while(!done);
            Unknown_0073e100();
            if(GetTopWindow(0)!=MainWindow) {
                Unknown_0073e100();
                SetForegroundWindow(MainWindow);
                ShowWindow(MainWindow,9);
                Unknown_0073e100();
            }
            for(int waits=10;waits;--waits) {
                Sleep(100);
                Unknown_0073e100();
            }
            }
        }
    } else Popup_005c3230(StringTable::Load_String(html_missing_label_007fd5fc,0,wol_source_file_007fd62c,0x4d8),0,Unknown_0073c120,0);
}
