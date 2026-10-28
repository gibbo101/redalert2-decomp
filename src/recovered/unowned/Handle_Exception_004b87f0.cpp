#include "shared/surface.hpp"
#include "shared/win32_api.hpp"
#include "shared/debug_printf.hpp"
#include "shared/dsurface.hpp"
WIN32_IMPORT int WINAPI lstrlenA(LPCSTR string);
WIN32_IMPORT DWORD WINAPI GetCurrentThreadId();
void __cdecl Unknown_00522e10();
struct _EXCEPTION_POINTERS;
void __fastcall Dump_Exception_004b7df0(_EXCEPTION_POINTERS *information);
int __fastcall Show_Exception_Dialog_004b7cf0();
void __fastcall Destroy_Exception_Window_005ff6e0(HWND window);
extern int exception_depth_007d6af8;
extern bool exception_flag_007d6afc;
extern char exception_text_00855ba8[];
extern DWORD main_thread_00b25f78;
extern HWND exception_window_00b25dd4;
extern bool unknown_flag_839c4c;
extern Surface *unknown_surface_839950;
// @ref ?unknown_surface_839950@@=00839950
// @ref ?unknown_surface_839954@@=00839954
extern Surface *unknown_surface_839964;
// @ref ?unknown_surface_839964@@=00839964
extern Surface *unknown_surface_839944;
// @ref ?unknown_surface_839944@@=00839944
extern Surface *unknown_surface_839948;
// @ref ?unknown_surface_839948@@=00839948
extern Surface *unknown_surface_839958;
// @ref ?unknown_surface_839958@@=00839958
// @ref ?Unknown_00522e10@@=00522e10
// @ref ?Dump_Exception_004b7df0@@=004b7df0
// @ref ?Show_Exception_Dialog_004b7cf0@@=004b7cf0
// @ref ?Destroy_Exception_Window_005ff6e0@@=005ff6e0
// @ref ?exception_depth_007d6af8@@=007d6af8
// @ref ?exception_flag_007d6afc@@=007d6afc
// @ref ?exception_text_00855ba8@@=00855ba8
// @ref ?main_thread_00b25f78@@=00b25f78
// @ref ?exception_window_00b25dd4@@=00b25dd4
// @ref ?unknown_flag_839c4c@@=00839c4c
extern char const exception_log_007d7ea0[];
// @ref ?exception_log_007d7ea0@@=007d7ea0
extern char const exception_filename_007d7e94[];
// @ref ?exception_filename_007d7e94@@=007d7e94
extern char const show_dialog_log_007d7e38[];
// @ref ?show_dialog_log_007d7e38@@=007d7e38
extern char const dialog_unavailable_log_007d7e4c[];
// @ref ?dialog_unavailable_log_007d7e4c@@=007d7e4c
// Original filter shims0068E270 and00690891 pass the exception code in ECX
// and the actual EXCEPTION_POINTERS in EDX. Code is unused by this body.
int __fastcall Handle_Exception_004b87f0(unsigned int exceptionCode, _EXCEPTION_POINTERS *information)
{
    Debug_Printf(exception_log_007d7ea0);
    Unknown_00522e10();
    ++exception_depth_007d6af8;
    if(exception_depth_007d6af8 == 0) {
        Dump_Exception_004b7df0(information);
        HANDLE file=CreateFileA(exception_filename_007d7e94,GENERIC_WRITE,0,0,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,0);
        if(file!=INVALID_HANDLE_VALUE) {
            DWORD written;
            WriteFile(file,exception_text_00855ba8,lstrlenA(exception_text_00855ba8),&written,0);
            CloseHandle(file);
        }
    }
    if (((unknown_surface_839950 && unknown_surface_839950->Is_Locked())
      || (unknown_surface_839954 && unknown_surface_839954->Is_Locked())
      || (unknown_surface_839964 && unknown_surface_839964->Is_Locked())
      || (unknown_surface_839944 && unknown_surface_839944->Is_Locked())
      || (unknown_surface_839948 && unknown_surface_839948->Is_Locked())
      || (unknown_surface_839958 && unknown_surface_839958->Is_Locked())) && unknown_flag_839c4c)
        goto unavailable;
    if (GetCurrentThreadId()!=main_thread_00b25f78) {
unavailable:
        Debug_Printf(dialog_unavailable_log_007d7e4c);
        return 0;
    }
    Debug_Printf(show_dialog_log_007d7e38);
    if(Show_Exception_Dialog_004b7cf0()!=0x481) return 0;
    exception_flag_007d6afc=false;
    if(exception_depth_007d6af8==0) exception_depth_007d6af8=-1;
    else if(exception_depth_007d6af8==2) return 0;
    if(exception_window_00b25dd4) Destroy_Exception_Window_005ff6e0(exception_window_00b25dd4);
    return 1;
}
