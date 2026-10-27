#include "shared/win32_api.hpp"
#include "shared/debug_printf.hpp"
struct DLGTEMPLATE;
typedef int (WINAPI *ExceptionDialogProc)(HWND,UINT,WPARAM,LPARAM);
WIN32_IMPORT BOOL WINAPI AllocConsole();
WIN32_IMPORT BOOL WINAPI FreeConsole();
WIN32_IMPORT void WINAPI Sleep(DWORD delay);
WIN32_IMPORT void WINAPI ExitProcess(UINT status);
WIN32_IMPORT int WINAPI DialogBoxIndirectParamA(HANDLE instance,DLGTEMPLATE const *dialog,HWND owner,ExceptionDialogProc procedure,LPARAM parameter);
WIN32_IMPORT int WINAPI DialogBoxParamA(HANDLE instance,LPCSTR name,HWND owner,ExceptionDialogProc procedure,LPARAM parameter);
void __cdecl Unknown_00522e10();
void *__fastcall Load_Resource_004954e0(unsigned int id,LPCSTR type);
int __stdcall Exception_Dialog_Procedure_004b7bf0(HWND,UINT,WPARAM,LPARAM);
int __cdecl Console_Printf_00796714(char const *,...);
int __cdecl Console_Read_Key_007963f7();
extern int exception_depth_007d6af8;
extern HANDLE game_instance_00b26180;
extern HWND game_window_00b263d8;
extern char const resource_found_007d79cc[];
extern char const resource_missing_007d79b8[];
extern char const recursive_exception_007d795c[];
// @ref ?Unknown_00522e10@@=00522e10
// @ref ?Load_Resource_004954e0@@=004954e0
// @ref ?Exception_Dialog_Procedure_004b7bf0@@=004b7bf0
// @ref ?Console_Printf_00796714@@=00796714
// @ref ?Console_Read_Key_007963f7@@=007963f7
// @ref ?exception_depth_007d6af8@@=007d6af8
// @ref ?game_instance_00b26180@@=00b26180
// @ref ?game_window_00b263d8@@=00b263d8
// @ref ?resource_found_007d79cc@@=007d79cc
// @ref ?resource_missing_007d79b8@@=007d79b8
// @ref ?recursive_exception_007d795c@@=007d795c
int __fastcall Show_Exception_Dialog_004b7cf0()
{
    Unknown_00522e10();
    switch(exception_depth_007d6af8) {
    default: {
        ShowCursor(1);
        DLGTEMPLATE const *dialog = (DLGTEMPLATE const *)Load_Resource_004954e0(247,(LPCSTR)5);
        int response;
        if(dialog) {
            Debug_Printf(resource_found_007d79cc);
            response=DialogBoxIndirectParamA(game_instance_00b26180,dialog,game_window_00b263d8,Exception_Dialog_Procedure_004b7bf0,0);
        } else {
            Debug_Printf(resource_missing_007d79b8);
            response=DialogBoxParamA(game_instance_00b26180,(LPCSTR)247,game_window_00b263d8,Exception_Dialog_Procedure_004b7bf0,0);
        }
        ShowCursor(0);
        return response;
    }
    case 3: ExitProcess(0); break;
    case 1:
        if(!AllocConsole()) {FreeConsole();AllocConsole();}
        Console_Printf_00796714(recursive_exception_007d795c);
        Sleep(4000);
        Console_Read_Key_007963f7();
        FreeConsole();
        break;
    case 2: break;
    }
    return 0x481;
}
