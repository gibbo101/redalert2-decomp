// Win32 window, dialog and common-control helpers in 0x00735690-0x007371AA (the
// translation unit after wincomm.cpp; no assert path, no RTTI). All free functions
// are __fastcall. Names are hypotheses from what each helper does.
#ifndef RA2_SHARED_WIN_UTIL_HPP
#define RA2_SHARED_WIN_UTIL_HPP

#include "shared/win32_api.hpp"
#include "shared/win32_gdi.hpp"
#include "shared/crt_string.hpp"
#include "shared/crt_memory.hpp"
#include "shared/vector_class.hpp"   // placement new

// Tree-view item (the SDK's TVITEMA) and its notification records.
struct TVITEMA {
    UINT mask;              // +0x00
    void *hItem;            // +0x04
    UINT state;             // +0x08
    UINT stateMask;         // +0x0C
    char *pszText;          // +0x10
    int cchTextMax;         // +0x14
    int iImage;             // +0x18
    int iSelectedImage;     // +0x1C
    int cChildren;          // +0x20
    LPARAM lParam;          // +0x24
};
struct NMHDR {
    HWND hwndFrom;          // +0x00
    UINT idFrom;            // +0x04
    UINT code;              // +0x08
};
struct NMTREEVIEWA {
    NMHDR hdr;              // +0x00
    UINT action;            // +0x0C
    TVITEMA itemOld;        // +0x10
    TVITEMA itemNew;        // +0x38
    POINT ptDrag;           // +0x60
};
struct NMTVDISPINFOA {
    NMHDR hdr;              // +0x00
    TVITEMA item;           // +0x0C
};

WIN32_IMPORT BOOL WINAPI RedrawWindow(HWND window, RECT const *update, void *region, UINT flags);
WIN32_IMPORT DWORD WINAPI GetWindowContextHelpId(HWND window);
WIN32_IMPORT BOOL WINAPI WinHelpA(HWND window, LPCSTR help_file, UINT command, DWORD data);

// The label-edit buffer (0x00B25F10) and the tree view of the current label edit or drag (0x00B25F30).
extern char *unknown_label_buffer_b25f10;
extern HWND unknown_tree_b25f30;

// Starts a tree-view label edit: limits the edit control to limit characters and remembers
// buffer and tree for the end (0x007367B0).
void __fastcall unknown_begin_label_edit_7367b0(HWND tree, char *buffer, int limit);
// Ends it (TVN_ENDLABELEDIT): trims the new text, copies it to the buffer, sets it as the
// item's text; its length, 0 when the edit was cancelled (0x007367F0).
int __fastcall unknown_end_label_edit_7367f0(NMTVDISPINFOA *info);
// TVN_ITEMEXPANDED: gives the item the closed or open image; true when expanded (0x00736750).
bool __fastcall unknown_set_expand_image_736750(HWND tree, NMTREEVIEWA *info, int closed_image, int open_image);
// Context help popup for a control (HELP_CONTEXTMENU in SUN.HLP; 0x007368A0).
void __fastcall unknown_context_help_7368a0(HWND window);
// The first combo box item at or after start whose item data is data; -1 if none (0x00736E10).
int __fastcall unknown_combo_find_data_736e10(HWND combo, int start, int data);
// Releases the game mouse and redraws window when active, captures it otherwise (0x00736E70).
void __fastcall unknown_mouse_activate_736e70(HWND window, short active);
// Centres window on its owner (0x00737060) / on parent's client area, the main window
// counting as the full screen (0x00737080).
void __fastcall unknown_center_on_owner_737060(HWND window);
void __fastcall unknown_center_window_737080(HWND window, HWND parent);
// Reads one byte in every 4 KB page of a buffer (page prefault; 0x00737160).
void __fastcall unknown_touch_pages_737160(char *buffer, int length);

// The dialog stack (shared/win32_window.hpp) and its users. Also declared in shared/queue.hpp
// (0x005B6000/0x005B6060), shared/gscreen.hpp (0x00A40D34) and shared/lobby.hpp (0x00735700,
// 0x007359E0): identical redeclarations so this unit does not include those headers.
extern int unknown_int_a40d34;
void __fastcall Unknown_005B6000(HWND dialog);
void __fastcall Unknown_005B6060(HWND dialog);
typedef long (__stdcall *UnknownDialogProc)(HWND window, unsigned message, unsigned wparam, long lparam);
// Creates dialog id from its template resource over parent, pushes it on the dialog stack, prepares
// it and its children (0x00735BC0), shows it when show is set and makes it the current dialog (0x00735700).
void *__fastcall unknown_create_dialog_735700(void *instance, int id, HWND parent, UnknownDialogProc procedure, long arg);
// Closes dialog (the top dialog when null) and every dialog above it on the stack, makes the one
// below current and records result (0x00B25DDC); false when dialog is not on the stack (0x007357E0;
// shared/unknown_globals.hpp still declares it as Unknown_007357E0(void *, int)).
bool __fastcall End_Dialog_007357e0(HWND dialog, int result);
extern int unknown_dialog_result_b25ddc;
// Called on a dialog before it is closed (0x005E5FC0; also declared in shared/owner_draw_dialog_control.hpp).
namespace OwnerDraw {
bool __fastcall unknown_5e5fc0(HWND dialog);
}
// Prepares a dialog control (EnumChildWindows callback; 0x00735BC0).
BOOL __stdcall unknown_prepare_control_735bc0(HWND window, LPARAM parameter);
// The dialog loop (0x007359E0; shared/lobby.hpp declares it as Unknown_007359e0 with int flags):
// runs the message loop until dialog leaves the stack, calling callback each pass (true ends the
// dialog with result 2); modal brackets it with message 0x4A9 (1 before, 0 after), show shows it;
// returns the dialog result (0x00B25DDC).
int __fastcall Dialog_Loop_007359e0(HWND dialog, bool (*callback)(), int unused, bool modal, bool show);
// Whether window is on the dialog stack (0x00735910).
int __fastcall unknown_is_listed_b25bb8(int key);
// Also declared in shared/movie.hpp, shared/ms_message_box.hpp and shared/wol_sink.hpp.
WIN32_IMPORT BOOL WINAPI TranslateMessage(MSG const *message);
WIN32_IMPORT LRESULT WINAPI DispatchMessageA(MSG const *message);
BOOL __fastcall unknown_peek_message_522ed0(MSG *message, HWND window, UINT first, UINT last, UINT remove);
extern int unknown_message_count_a52298;
void __fastcall unknown_517370(bool unknown1);
extern bool unknown_b2abd9;
// Tree-view item dragging: the drag is on (0x00B25F2C), the dragged item (0x00B25F34) and its
// drag image list (0x00B25F38).
extern bool unknown_dragging_b25f2c;
extern void *unknown_drag_item_b25f34;
extern void *unknown_drag_image_b25f38;
WIN32_IMPORT BOOL WINAPI ImageList_BeginDrag(void *image_list, int track, int hotspot_x, int hotspot_y);
WIN32_IMPORT BOOL WINAPI ImageList_DragEnter(HWND lock, int x, int y);
WIN32_IMPORT BOOL WINAPI ImageList_DragMove(int x, int y);
WIN32_IMPORT BOOL WINAPI ImageList_DragShowNolock(BOOL show);
WIN32_IMPORT void WINAPI ImageList_EndDrag();
WIN32_IMPORT BOOL WINAPI ImageList_Destroy(void *image_list);
WIN32_IMPORT HWND WINAPI ChildWindowFromPoint(HWND parent, POINT point);
// Where a dragged item is: the window under the cursor, the window that takes the drop (that
// window's parent, or the window itself when it is the tree's parent), the tree and item, the
// cursor in screen and client coordinates, and the cursor relative to the window (40 bytes).
struct UnknownDragInfo {
    HWND Window;            // +0x00
    HWND Target;            // +0x04
    HWND Tree;              // +0x08
    void *Item;             // +0x0C
    POINT Screen;           // +0x10
    POINT Client;           // +0x18
    POINT Offset;           // +0x20
};
// TVN_BEGINDRAG: asks dialog (message 0x4C9) whether the item may be dragged; starts the drag
// image, captures the mouse and starts the scroll timer; whether a drag is on (0x00736230).
bool __fastcall unknown_begin_drag_736230(HWND dialog, HWND tree, NMTREEVIEWA *info);
UnknownDragInfo __fastcall unknown_drag_info_736490(unsigned long position);     // 0x00736490
// The scroll timer (id 1): scrolls the tree one item towards the cursor above or below it,
// faster the farther away (0x00736570).
void __fastcall unknown_drag_scroll_736570(int timer);
// WM_MOUSEMOVE during a drag: asks the target (message 0x4C8) whether it takes the drop, sets the
// arrow or no-drop cursor and moves the drag image; whether it does (0x00736670).
bool __fastcall unknown_drag_move_736670(unsigned long position);
class INIClass;
// Window positions in an INI file: the section of the window being saved or restored, read by the
// child callbacks (0x00B25F28). Restoring moves window to section's X/Y kept on screen, then gives
// each tree view its saved expanded items ("TV<n>") and each list view its column widths ("LV<n>")
// through 0x007368F0 (0x00736A70); saving is 0x00736CD0 with 0x00736B40.
extern char const *unknown_window_section_b25f28;
void __fastcall unknown_restore_window_position_736a70(char const *section, HWND window, INIClass &ini);
BOOL __stdcall unknown_restore_child_window_7368f0(HWND window, long parameter);
BOOL __stdcall unknown_save_child_window(HWND window, long parameter);
// Whether window's class is class_name (inline in 0x007368F0 and 0x00736B40).
extern "C" int __cdecl strcmp(char const *left, char const *right);
inline bool Is_Window_Class(HWND window, char const *class_name)
{
    char name[64];
    GetClassNameA(window, name, sizeof(name));
    return strcmp(name, class_name) == 0;
}
// Control layout: dialog templates are laid out for a 300 x 163 client area (0x007FD048,
// 0x007FD04C); 0x00735BC0 scales each control by the client size of template 0xC6 (measured once
// into 0x00B25DE4) and moves it. 0x00735B40 is that template's (empty) dialog procedure.
extern int unknown_layout_width_7fd048;
extern int unknown_layout_height_7fd04c;
extern LONG unknown_template_size_b25de4[2];
BOOL __stdcall unknown_null_dialog_proc_735b40(HWND dialog, UINT message, WPARAM wparam, LPARAM lparam);
// WM_LBUTTONUP during a drag: moves the drag image a last time (0x00736670), ends the drag, offers
// the drop to the target (message 0x4CA) when it takes it, stops the scroll timer and clears the
// drop highlight; false when no drag is on (0x00736320).
bool __fastcall unknown_end_drag_736320(unsigned long position);
// Fonts: a font of face at width x height device units (logical after the DC's mapping) with
// attribute bits 1 bold, 2 italic, 4 underline, 8 strike-out; with a width, the face's average
// character width is scaled to it (Petzold's EzCreateFont shape; 0x007360B0).
typedef struct HFONT__ *HFONT;
struct LOGFONTA {
    LONG lfHeight;                  // +0x00
    LONG lfWidth;                   // +0x04
    LONG lfEscapement;              // +0x08
    LONG lfOrientation;             // +0x0C
    LONG lfWeight;                  // +0x10
    unsigned char lfItalic;         // +0x14
    unsigned char lfUnderline;      // +0x15
    unsigned char lfStrikeOut;      // +0x16
    unsigned char lfCharSet;        // +0x17
    unsigned char lfOutPrecision;   // +0x18
    unsigned char lfClipPrecision;  // +0x19
    unsigned char lfQuality;        // +0x1A
    unsigned char lfPitchAndFamily; // +0x1B
    char lfFaceName[32];            // +0x1C
};
struct TEXTMETRICA {
    LONG tmHeight;                  // +0x00
    LONG tmAscent;                  // +0x04
    LONG tmDescent;                 // +0x08
    LONG tmInternalLeading;         // +0x0C
    LONG tmExternalLeading;         // +0x10
    LONG tmAveCharWidth;            // +0x14
    LONG tmMaxCharWidth;            // +0x18
    LONG tmWeight;                  // +0x1C
    LONG tmOverhang;                // +0x20
    LONG tmDigitizedAspectX;        // +0x24
    LONG tmDigitizedAspectY;        // +0x28
    unsigned char tmFirstChar, tmLastChar, tmDefaultChar, tmBreakChar;   // +0x2C
    unsigned char tmItalic, tmUnderlined, tmStruckOut, tmPitchAndFamily; // +0x30
    unsigned char tmCharSet;        // +0x34
};
struct XFORM;
WIN32_IMPORT int WINAPI SaveDC(HDC dc);
WIN32_IMPORT BOOL WINAPI RestoreDC(HDC dc, int saved);
WIN32_IMPORT int WINAPI SetGraphicsMode(HDC dc, int mode);
WIN32_IMPORT BOOL WINAPI ModifyWorldTransform(HDC dc, XFORM const *transform, DWORD mode);
WIN32_IMPORT BOOL WINAPI SetViewportOrgEx(HDC dc, int x, int y, POINT *old);
WIN32_IMPORT BOOL WINAPI SetWindowOrgEx(HDC dc, int x, int y, POINT *old);
WIN32_IMPORT BOOL WINAPI DPtoLP(HDC dc, POINT *points, int count);
WIN32_IMPORT HFONT WINAPI CreateFontIndirectA(LOGFONTA const *font);
WIN32_IMPORT BOOL WINAPI GetTextMetricsA(HDC dc, TEXTMETRICA *metrics);
HFONT __fastcall unknown_create_font_7360b0(HDC dc, char const *face, int width, int height, unsigned attributes);
// The font cache: fonts made by 0x007360B0, found by face, size and attributes (0x00735DB0);
// 0x00735D90 empties it (the capacity is kept). A plain growable array at 0x00B25DC8.
struct UnknownFontEntry {
    char Face[128];                 // +0x00
    int Width;                      // +0x80
    int Height;                     // +0x84
    unsigned Attributes;            // +0x88
    HFONT Font;                     // +0x8C
};
struct UnknownFontCache {
    int Count;                      // +0x00 (0x00B25DC8)
    int Max;                        // +0x04 (0x00B25DCC)
    UnknownFontEntry *Vector;       // +0x08 (0x00B25DD0)

    // Copies element index into entry when it exists.
    void Get(int index, UnknownFontEntry &entry) const
    {
        if (index >= 0 && index < Count) {
            entry = Vector[index];
        }
    }
    void Grow()
    {
        if (Count >= Max) {
            int max = Count * 2;
            if (max < 10) {
                max = 10;
            }
            UnknownFontEntry *vector = (UnknownFontEntry *)operator new(max * sizeof(UnknownFontEntry));
            memset(vector, 0, max * sizeof(UnknownFontEntry));
            if (Vector != 0) {
                memcpy(vector, Vector, Count * sizeof(UnknownFontEntry));
            }
            operator delete(Vector);
            Vector = vector;
            Max = max;
        }
    }
    void Insert(int index, UnknownFontEntry const &entry)
    {
        if (index > Count) {
            index = Count;
        }
        if (index >= Max) {
            Grow();
        }
        Grow();
        if (index < Count) {
            memmove(&Vector[index + 1], &Vector[index], (Count - index) * sizeof(UnknownFontEntry));
        }
        new (&Vector[index]) UnknownFontEntry(entry);
        Count++;
    }
    void Add(UnknownFontEntry const &entry) { Insert(Count, entry); }
};
extern UnknownFontCache unknown_font_cache_b25dc8;
void unknown_clear_font_cache_735d90();
// The cached font of face at width x height with attributes, made and cached when missing; 0 when
// dc is null and the font is not cached (0x00735DB0).
HFONT __fastcall unknown_find_font_735db0(HDC dc, char const *face, int width, int height, unsigned attributes);

#endif
