// The debug text window's module state (0x0059D900-0x0059DCE0): eight MonoClass
// pages and the dialog that shows the one on display. Names are hypotheses.
#ifndef RA2_SHARED_MONO_WINDOW_HPP
#define RA2_SHARED_MONO_WINDOW_HPP
#include "shared/mono_class.hpp"
#include "shared/win32_gdi.hpp"

// GDI and window declarations only this unit uses.
struct LOGFONTA {
    LONG lfHeight, lfWidth, lfEscapement, lfOrientation, lfWeight;
    unsigned char lfItalic, lfUnderline, lfStrikeOut, lfCharSet;
    unsigned char lfOutPrecision, lfClipPrecision, lfQuality, lfPitchAndFamily;
    char lfFaceName[32];
};
struct TEXTMETRICA {
    LONG tmHeight, tmAscent, tmDescent, tmInternalLeading, tmExternalLeading;
    LONG tmAveCharWidth, tmMaxCharWidth, tmWeight, tmOverhang, tmDigitizedAspectX, tmDigitizedAspectY;
    unsigned char tmFirstChar, tmLastChar, tmDefaultChar, tmBreakChar;
    unsigned char tmItalic, tmUnderlined, tmStruckOut, tmPitchAndFamily, tmCharSet;
};
WIN32_IMPORT int WINAPI GetDeviceCaps(HDC dc, int index);
WIN32_IMPORT int WINAPI MulDiv(int number, int numerator, int denominator);
typedef struct HFONT__ *HFONT;
WIN32_IMPORT HFONT WINAPI CreateFontIndirectA(LOGFONTA const *font);
WIN32_IMPORT BOOL WINAPI GetTextMetricsA(HDC dc, TEXTMETRICA *metrics);
WIN32_IMPORT DWORD WINAPI GetSysColor(int index);
WIN32_IMPORT BOOL WINAPI AdjustWindowRect(RECT *rect, DWORD style, BOOL menu);
extern "C" char *__cdecl strcpy(char *destination, char const *source);
#pragma intrinsic(strcpy)

extern MonoClass *unknown_mono_pages_a70e40[8];   // 0x00A70E40
extern void *unknown_mono_instance_a70f00;        // 0x00A70F00 HINSTANCE for the dialog
extern HWND__ *unknown_mono_parent_a70f04;        // 0x00A70F04 game window (owner, focus)
extern bool unknown_mono_allowed_a70f08;          // 0x00A70F08
extern bool unknown_mono_requested_a70f09;        // 0x00A70F09 asked for before a parent existed

extern TEXTMETRICA unknown_mono_metrics_a70ea0;     // 0x00A70EA0 (tmHeight, tmExternalLeading, tmMaxCharWidth
                                                  // are read as unknown_mono_height/leading/width)
BOOL __stdcall Mono_Dialog_Proc_0059dce0(HWND__ *dialog, unsigned int message, unsigned int wparam, long lparam);
// Keeps the dialog's instance, the game window and whether the window may show, builds the
// eight pages and shows the window if it was asked for before (0x0059D780; name hypothesis).
void __fastcall Mono_Window_Init(void *instance, HWND__ *parent, bool allowed);
void Mono_Window_Shutdown();                      // 0x0059D900
void Mono_Window_Show_Requested();                // 0x0059D970
void Mono_Window_Show();                          // 0x0059D9C0
void Mono_Window_Hide();                          // 0x0059DA00
void Mono_Clear_All_Pages();                      // 0x0059DAD0
void Mono_Window_Create();                        // 0x0059DB30

// Modeless dialog registry of the audio file unit (0x00522B20 add, 0x00522B80 remove).
void __fastcall Unknown_Add_Modeless_Dialog_00522b20(HWND__ *dialog);
void __fastcall Unknown_Remove_Modeless_Dialog_00522b80(HWND__ *dialog);
#endif
