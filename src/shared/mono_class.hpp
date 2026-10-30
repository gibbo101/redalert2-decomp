// The debug text window: an 80 x 25 character grid with a colour attribute per
// cell, drawn through GDI on the game window. The name and the member names are
// Westwood's mono-monitor vocabulary (TS/RA1 MonoClass), a hypothesis here.
// 0x00A70F0A turns it on; 0x00A70F0C is the grid on display.
#ifndef RA2_SHARED_MONO_CLASS_HPP
#define RA2_SHARED_MONO_CLASS_HPP
struct HDC__;
struct HWND__;
#include "shared/rect.hpp"
typedef unsigned short wchar_t;

// The pixel position of a character cell (constructor 0x0059E160).
struct MonoPoint : Point2D {
    MonoPoint(int column, int row);
};

extern bool unknown_mono_enabled_a70f0a;       // 0x00A70F0A

class MonoClass {
public:
    MonoClass(int handle);                                    // 0x0059E190
    int Get_Handle() const { return Handle; }                 // 0x0059E230
    void Set_Cursor(int x, int y);                         // 0x0059E240
    void Window(int x, int y, int width, int height);         // 0x0059E260
    void Clear();                                         // 0x0059E290
    bool Is_Changed() const { return Changed; }               // 0x0059E2E0
    void View();                                              // 0x0059E2F0
    void Set_Attribute(int attribute)                         // 0x0059E370
    {
        if (unknown_mono_enabled_a70f0a) {
            Attribute = attribute;
        }
    }
    void Fill_Attrib(int x, int y, int width, int height, int attribute);   // 0x0059E390
    void Scroll(int lines);                                   // 0x0059E410
    void Pan(int columns);                                    // 0x0059E590
    void Print(char const *text);                             // 0x0059E6D0
    void Printf(char const *format, ...);                     // 0x0059E7F0
    void Printf(wchar_t const *format, ...);                  // 0x0059E840
    void Text_Print(char const *text, int x, int y, int attribute);   // 0x0059E8A0
    void Text_Print(wchar_t const *text, int x, int y, int attribute);   // 0x0059E8E0
    char Map_Character(char character) const;                // 0x0059E960
    void Draw_Character(HDC__ *dc, int x, int y);                // 0x0059E9D0
    void Refresh(int x, int y, int width, int height);        // 0x0059EA90

    char Characters[80][25];            // +0x0000 by column, then row
    int Attributes[80][25];             // +0x07D0
    int Attribute;                      // +0x2710 the attribute new text gets
    int DrawnAttribute;                 // +0x2714 the attribute GDI is set up for
    int Handle;                         // +0x2718
    int X;                              // +0x271C cursor
    int Y;                              // +0x2720
    int WindowX;                        // +0x2724
    int WindowY;                        // +0x2728
    int WindowWidth;                    // +0x272C
    int WindowHeight;                   // +0x2730
    bool Changed;                       // +0x2734
};

extern MonoClass *unknown_mono_viewed_a70f0c;  // 0x00A70F0C
extern HWND__ *unknown_mono_window_a70f10;        // 0x00A70F10
extern void *unknown_mono_font_a70f14;       // 0x00A70F14
extern int unknown_mono_height_a70ea0;         // 0x00A70EA0
extern int unknown_mono_leading_a70eb0;        // 0x00A70EB0
extern int unknown_mono_width_a70eb8;          // 0x00A70EB8
extern unsigned long unknown_mono_text_color_a70de8;   // 0x00A70DE8
extern unsigned long unknown_mono_back_color_a70e00;   // 0x00A70E00

extern "C" unsigned int __cdecl strlen(char const *string);
#pragma intrinsic(strlen)
extern "C" int __cdecl sprintf(char *buffer, char const *format, ...);              // 0x007820F4
extern "C" int __cdecl vsprintf(char *buffer, char const *format, char *arguments);  // 0x007849BA
extern "C" int __cdecl vswprintf(wchar_t *buffer, wchar_t const *format, char *arguments);   // 0x00783A58

#endif
