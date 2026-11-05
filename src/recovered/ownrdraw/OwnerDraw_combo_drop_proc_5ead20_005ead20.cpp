// @ref ?unknown_combo_owner_a763f4@OwnerDraw@@3PAUHWND__@@A=00a763f4
// @ref ?unknown_dropdown_owner_a763e8@OwnerDraw@@3PAUHWND__@@A=00a763e8
// @ref ?unknown_dropdown_window_a763e4@OwnerDraw@@3PAUHWND__@@A=00a763e4
// @ref _?solid_brush@?1??unknown_combo_drop_proc_5ead20@OwnerDraw@@YGJPAUHWND__@@IIJ@Z@4PAXA=00a733e0
// @ref _?$S83@?1??unknown_combo_drop_proc_5ead20@OwnerDraw@@YGJPAUHWND__@@IIJ@Z@4EA=00a73438
// @ref ??_C@_09LALL@Scrollbar?$AA@=007ead08
// @ref ??_C@_0BM@PKCO@Dropd?$DN?$CFp?5?5Master?$DN?$CFp?5?5Dlg?$DN?$CFp?$AA@=007ead14
// @ref ??_C@_0CC@ECNN@ComboBox?5dropdown?5windata?5?$DN?5NULL@=007ead38
// @ref ??_C@_17LKCM@?$AA?4?$AA?4?$AA?4?$AA?$AA@=007ead30
// @ref ??_C@_11A@?$AA?$AA@=00839d4c
// @ref __imp__SendMessageA@16=0079a4a0
// @ref __imp__CreateSolidBrush@4=0079a074
// @ref __imp__GetClientRect@8=0079a4b8
// @ref __imp__GetParent@4=0079a500
// @ref __imp__BringWindowToTop@4=0079a4bc
// @ref __imp__CallWindowProcA@20=0079a4c0
// @ref __imp__ValidateRect@8=0079a3f8
// @ref __imp__GetWindowRect@8=0079a398
// @ref __imp__SetCapture@4=0079a3f0
// @ref __imp__GetCapture@0=0079a3ec
// @ref __imp__ReleaseCapture@0=0079a3e8
// @ref __imp__SetTimer@16=0079a4d4
// @ref __imp__KillTimer@8=0079a4c4
// @ref __imp__Sleep@4=0079a1e4
// @ref __imp__InvalidateRect@12=0079a494
// @ref __imp__GetDlgItem@8=0079a49c
// @ref __imp__GetWindowLongA@8=0079a48c
// @ref __imp__SetWindowLongA@12=0079a488
// @ref __imp__DestroyWindow@4=0079a3d4
// @ref __imp__PostMessageA@16=0079a470
// @ref __imp__CreateWindowExA@48=0079a4c8
// @ref __imp__SetWindowPos@28=0079a3d0
// @ref __imp__ShowWindow@8=0079a498
// @ref __imp__UpdateWindow@4=0079a46c
// @ref __imp__DefWindowProcA@16=0079a388
#include "shared/win32_api.hpp"
#include "shared/win32_window.hpp"
#include "shared/surface.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/hicolor.hpp"
#include "shared/text_print.hpp"
#include "shared/rules.hpp"
#include "shared/sound_play.hpp"
#include "shared/debug_printf.hpp"
#include "shared/crt_memory.hpp"
#include "shared/mono_window.hpp"
#include "shared/rect.hpp"
#include "shared/owner_draw_dialog_control.hpp"

// @ref _wcscat=0078365f
// @ref _wcscmp=007837d3
// @ref _wcsncpy=00783622
// @ref _wcslen=00783605
// @ref _sprintf=007820f4
extern "C" wchar_t *__cdecl wcscat(wchar_t *destination, wchar_t const *source);
extern "C" int __cdecl wcscmp(wchar_t const *a, wchar_t const *b);
extern "C" wchar_t *__cdecl wcsncpy(wchar_t *destination, wchar_t const *source, unsigned int count);
extern "C" unsigned int __cdecl wcslen(wchar_t const *string);
extern "C" int __cdecl sprintf(char *buffer, char const *format, ...);
// @ref ?ProgramInstance@@3PAXA=00b26180
extern void *ProgramInstance;

extern "C" __declspec(dllimport) void *__stdcall CreateSolidBrush(unsigned long color);
WIN32_IMPORT BOOL WINAPI BringWindowToTop(HWND window);

namespace OwnerDraw {

BOOL __stdcall unknown_restore_child_5edd30(HWND window, LPARAM lparam);
BOOL __stdcall unknown_5ed180(HWND window, LPARAM lparam);
int __fastcall unknown_draw_text_5fe020(Surface *surface, wchar_t const *text, RECT *area, BitFontClass *font,
    unsigned long color, int flags, int unknown7, int unknown8, int arg9, int arg10);

// The combo box whose list is dropped, its dialog and the drop window (TibSun OwnerComboHandle, _dropdown_owner,
// _dropdown_window).
HWND unknown_combo_owner_a763f4;
HWND unknown_dropdown_owner_a763e8;
HWND unknown_dropdown_window_a763e4;

struct UnknownScrollInfo {
    unsigned int cbSize;
    unsigned int fMask;
    int nMin;
    int nMax;
    unsigned int nPage;
    int nPos;
    int nTrackPos;
};

struct UnknownListItem {
    int unknown_00;
    int unknown_04;
    wchar_t *text;
};

// The wide text of a list item through the control's original procedure.
inline int Get_Item_Text(HWND owner, int const &index, wchar_t *text, int size)
{
    WNDPROC proc = 0;
    WNDPROC *found = 0;
    unknown_window_procs_a73688.Get(owner, found);
    if (found) {
        proc = *found;
    }
    text[0] = 0;
    int item = CallWindowProcA(proc, owner, 0x199, index, 0);
    if (item == -1 || item == 0) {
        item = CallWindowProcA(proc, owner, 0x150, index, 0);
    }
    if (item != -1 && item != 0) {
        wcsncpy(text, ((UnknownListItem *)item)->text, size);
        text[size - 1] = 0;
        return wcslen(text);
    }
    return 0;
}

// The drop-down list window procedure of a combo box (0x005EAD20; TibSun ComboDropWinCtrlProc).
LRESULT __stdcall unknown_combo_drop_proc_5ead20(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
{
    static void *solid_brush = CreateSolidBrush(0x306030);
    RECT rect;
    Window_Rect_In_Main_Client(window, &rect);
    RECT client;
    GetClientRect(window, &client);
    // Function scope: the frame shows it live across every switch case (nothing shares its slot).
    Rect fill;
    RECT parent_rect;
    memset(&parent_rect, 0, sizeof(parent_rect));
    int scrollbar_width = 2 * unknown_color_a73928 + 18;
    int need_scrollbar = -1;
    int max_top = 0;
    HWND parent = 0;
    if (unknown_combo_owner_a763f4) {
        parent = GetParent(unknown_combo_owner_a763f4);
    }
    UnknownControlRecord *parent_data = 0;
    if (parent) {
        unknown_registry_a73640.Get((unsigned int const &)parent, parent_data);
        Window_Rect_In_Main_Client(parent, &parent_rect);
    }
    unknown_dropdown_owner_a763e8 = parent;
    unknown_dropdown_window_a763e4 = window;
    UnknownControlRecord *data = 0;
    unknown_registry_a73640.Get((unsigned int const &)window, data);
    if (data == 0) {
        Debug_Printf("ComboBox dropdown windata = NULL\n");
    }
    UnknownControlRecord *master = 0;
    if (unknown_combo_owner_a763f4) {
        unknown_registry_a73640.Get((unsigned int const &)unknown_combo_owner_a763f4, master);
    }
    if (message != 0x146 && message != 0x154 && message != 0x115) {
        int item_count = SendMessageA(unknown_combo_owner_a763f4, 0x146, 0, 0);
        int item_height = SendMessageA(unknown_combo_owner_a763f4, 0x154, 0, 0);
        if (item_height <= 1) {
            item_height = 1;
        }
        need_scrollbar = item_count * item_height > client.bottom - client.top;
        max_top = item_count - (client.bottom - client.top) / item_height;
        if (data) {
            if ((unsigned int)data->attached_0c > 1) {
                UnknownScrollInfo info;
                info.fMask = 5;
                info.nMin = 0;
                info.nMax = max_top;
                info.nPos = data->unknown_f0;
                info.cbSize = 0x1c;
                SendMessageA(data->attached_0c, 0xe9, 0, (LPARAM)&info);
            }
            if (data->attached_0c) {
                BringWindowToTop(data->attached_0c);
            }
        }
    }
    switch (message) {
    case 0x14:
        return 0;
    case 1: {
        SetCapture(window);
        unknown_combo_owner_a763f4 = *(HWND *)lparam;
        char buffer[100];
        sprintf(buffer, "Dropd=%p  Master=%p  Dlg=%p", window, unknown_combo_owner_a763f4, GetParent(unknown_combo_owner_a763f4));
        Debug_Printf(buffer);
        SetTimer(window, 0, 20, 0);
        return 0;
    }
    case 0x82:
        unknown_dropdown_window_a763e4 = 0;
        unknown_dropdown_owner_a763e8 = 0;
        ReleaseCapture();
        KillTimer(window, 0);
        break;
    case 0x115: {
        int top = SendMessageA(data->attached_0c, 0xe1, 0, 0);
        if (top != SendMessageA(window, 0x15b, 0, 0)) {
            SendMessageA(window, 0x15c, top, 0);
        }
        break;
    }
    case 0x113: {
        HWND capture = GetCapture();
        if (capture == window) {
            ReleaseCapture();
            Sleep(0);
            SetCapture(capture);
        }
        break;
    }
    case 0x15b:
        if (data) {
            return data->unknown_f0;
        }
        break;
    case 0x200: {
        int x = lparam & 0xffff;
        int y = (unsigned int)lparam >> 16;
        int index = SendMessageA(window, 0x4e8, 0, (y << 16) | x);
        if (index != -1) {
            if (data->unknown_e8 != index) {
                InvalidateRect(window, 0, 0);
            }
            data->unknown_e8 = index;
            HWND tip = GetDlgItem(parent, 0x695);
            if (tip) {
                WideString text;
                text = unknown_5e2100(parent, (int)unknown_combo_owner_a763f4, index);
                if (wcscmp((wchar_t const *)text.Get(), L"")) {
                    SendMessageA(tip, 0x4b2, 0, (LPARAM)text.unknown_text_770430());
                } else {
                    text = unknown_5e2160(parent, (int)unknown_combo_owner_a763f4);
                    if (wcscmp((wchar_t const *)text.Get(), L"")) {
                        SendMessageA(tip, 0x4b2, 0, (LPARAM)text.unknown_text_770430());
                    }
                }
            }
        }
        return 0;
    }
    case 0x15c: {
        int top = wparam;
        int item_count = SendMessageA(unknown_combo_owner_a763f4, 0x146, 0, 0);
        int item_height = SendMessageA(unknown_combo_owner_a763f4, 0x154, 0, 0);
        if (!item_count || !item_height) {
            break;
        }
        int visible = (client.bottom - client.top) / item_height;
        if (top < 0) {
            top = 0;
        }
        int limit = item_count - visible;
        if (limit > 0) {
            if (top > limit) {
                top = limit;
            }
        } else {
            top = 0;
        }
        if (top != data->unknown_f0) {
            data->unknown_f0 = top;
            InvalidateRect(window, 0, 0);
        }
        return 0;
    }
    case 0x201:
    case 0x203: {
        int x = lparam & 0xffff;
        int y = (unsigned int)lparam >> 16;
        if (x > client.right && x < client.right + data->scroll_width_04 && y > 0 && y < client.bottom) {
            SendMessageA(data->attached_0c, message, wparam, lparam);
            break;
        }
        Voc_Play(Rules->GUIComboCloseSound, 1.0f, 0x2000, 0);
        if (x >= 0 && y >= 0 && x <= client.right && y <= client.bottom) {
            int item_height = SendMessageA(unknown_combo_owner_a763f4, 0x154, 0, 0);
            int item_count = SendMessageA(unknown_combo_owner_a763f4, 0x146, 0, 0);
            int index = y / item_height;
            if (data) {
                index += data->unknown_f0;
            }
            int clamped = index < 0 ? 0 : index;
            int max_index = item_count - 1;
            if (max_index < clamped) {
                clamped = max_index;
            }
            SendMessageA(unknown_combo_owner_a763f4, 0x14e, clamped, 0);
            int id = GetWindowLongA(unknown_combo_owner_a763f4, -12);
            if (need_scrollbar) {
                DestroyWindow(data->attached_0c);
            }
            ReleaseCapture();
            SendMessageA(unknown_combo_owner_a763f4, 0x14f, 0, 0);
            PostMessageA(parent, 0x111, (id & 0xffff) | 0x10000, (LPARAM)unknown_combo_owner_a763f4);
            return 0;
        }
        if (need_scrollbar) {
            DestroyWindow(data->attached_0c);
        }
        ReleaseCapture();
        SendMessageA(unknown_combo_owner_a763f4, 0x14f, 0, 0);
        return 0;
    }
    case 0x4e8: {
        int x = lparam & 0xffff;
        int y = (unsigned int)lparam >> 16;
        int result = -1;
        if (x >= 0 && y >= 0 && x < client.right && y < client.bottom) {
            int item_height = SendMessageA(unknown_combo_owner_a763f4, 0x154, 0, 0);
            int item_count = SendMessageA(unknown_combo_owner_a763f4, 0x146, 0, 0);
            int index = y / item_height + data->unknown_f0;
            int clamped = index < 0 ? 0 : index;
            int max_index = item_count - 1;
            if (max_index < clamped) {
                clamped = max_index;
            }
            result = clamped;
        }
        return result;
    }
    case 0x4ea:
        return (LRESULT)unknown_combo_owner_a763f4;
    case 0x7e8:
        data->unknown_e8 = SendMessageA(unknown_combo_owner_a763f4, 0x147, 0, 0);
        return 0;
    // Last in the source: case 0x14 jumps into the epilogue of the last `return 0` written.
    case 0xf: {
        BitFontClass *font = parent_data->font_64;
        int item_count = SendMessageA(unknown_combo_owner_a763f4, 0x146, 0, 0);
        int item_height = SendMessageA(unknown_combo_owner_a763f4, 0x154, 0, 0);
        int client_height = client.bottom - client.top;
        Rect dest_rect(rect.left, rect.top, rect.right - rect.left, client_height);
        int selected = data->unknown_e8;
        Rect src;
        src.X = rect.left - parent_rect.left;
        src.Y = rect.top - parent_rect.top;
        src.Width = client.right;
        src.Height = client.bottom;
        if (data->surface_10 == 0) {
            Rect dst(0, 0, client.right, client.bottom);
            BSurface *surface = new BSurface(client.right, client.bottom, 2);
            data->surface_10 = surface;
            unknown_surface_count_a763d8++;
            if (parent_data && parent_data->surface_10) {
                surface->Copy_From(dst, *parent_data->surface_10, src, false, true);
            }
            int total = client.right * client.bottom;
            unsigned short *pixels = (unsigned short *)surface->Lock();
            for (int i = 0; i < total; i++) {
                unsigned short pixel = pixels[i];
                pixels[i] = Blend_Color(pixel, 0, data->unknown_c8);
            }
            surface->Unlock();
        }
        {
            Rect from;
            from.X = 0;
            from.Y = 0;
            from.Width = dest_rect.Width;
            from.Height = dest_rect.Height;
            unknown_surface_839958->Copy_From(dest_rect, *data->surface_10, from, false, true);
        }
        Rect frame(dest_rect);
        int color = unknown_5fda40(unknown_color_a76158);
        if (master && master->alternate_cd) {
            color = unknown_5fda40(unknown_color_a73910);
        }
        unknown_5fdb20(unknown_surface_839958, frame, 1, color);
        if (need_scrollbar && data && data->attached_0c) {
            Rect outer(dest_rect);
            outer.Width += scrollbar_width;
            unknown_5fdb20(unknown_surface_839958, outer, 1, color);
        }
        int first = data->unknown_f0;
        Rect row;
        for (int index = first; index < item_count; index++) {
            row.X = rect.left;
            int width = rect.right - rect.left;
            row.Y = (index - first) * item_height + rect.top;
            if ((index - first) * item_height + item_height > client_height) {
                break;
            }
            wchar_t text[128];
            Get_Item_Text(unknown_combo_owner_a763f4, index, text, 0x80);
            if (index == selected) {
                fill.X = row.X;
                fill.Y = row.Y;
                fill.Width = width;
                fill.Height = item_height;
                int fill_color;
                if (master ? master->alternate_cd : false) {
                    fill_color = unknown_5fda40(unknown_color_a763b0);
                } else {
                    fill_color = unknown_5fda40(unknown_color_a7613c);
                }
                unknown_surface_839958->Fill_Rect(fill, fill_color);
            }
            RECT text_rect;
            text_rect.top = row.Y;
            text_rect.left = row.X + 3;
            text_rect.right = row.X + width;
            text_rect.bottom = row.Y + item_height;
            unsigned long text_color = unknown_color_a733e4;
            if (master && master->alternate_cd) {
                text_color = unknown_color_a737e8;
            }
            if (index < 50 && master && master->item_colors_110[index] >= 0) {
                text_color = master->item_colors_110[index];
                if (master->item_fills_cc) {
                    Rect fill2;
                    fill2.X = row.X;
                    fill2.Y = row.Y;
                    fill2.Width = width;
                    fill2.Height = item_height;
                    Unknown_Rect_Shrink_006F1B00(&fill2, 2);
                    unknown_surface_839958->Fill_Rect(fill2, unknown_5fda40(text_color));
                }
            }
            int max_width = client.right - 20;
            int length = wcslen(text);
            int text_width = font->String_Pixel_Width(text, 0);
            while (length && text_width > max_width) {
                length--;
                text[length] = 0;
                wcscat(text, L"...");
                text_width = font->String_Pixel_Width(text, 0);
            }
            unknown_draw_text_5fe020(unknown_surface_839958, text, &text_rect, font, text_color, 4, 12, 0, 0, 0);
        }
        unknown_surface_839958->Lock();
        unknown_surface_839950->Lock();
        Rect screen(dest_rect);
        RECT window_rect;
        GetWindowRect(window, &window_rect);
        screen.X += window_rect.left - rect.left;
        screen.Y += window_rect.top - rect.top;
        unknown_surface_839950->Copy_From(screen, *unknown_surface_839958, dest_rect, false, true);
        unknown_surface_839950->Unlock();
        unknown_surface_839958->Unlock();
        ValidateRect(window, 0);
        return 0;
    }
    case 2:
        Unknown_Remove_Modeless_Dialog_00522b80(window);
        break;
    }
    if (need_scrollbar == 1) {
        if (data && !data->attached_0c) {
            data->attached_0c = (HWND)1;
            GetWindowLongA(window, -12);
            parent = GetParent(window);
            RECT parent_display;
            Window_Rect_In_Main_Client(parent, &parent_display);
            RECT drop_display;
            Window_Rect_In_Main_Client(window, &drop_display);
            int left = drop_display.left - parent_display.left;
            int top = drop_display.top - parent_display.top;
            bool alternate = false;
            int x = left - scrollbar_width + client.right;
            int y = top + client.top;
            int height = drop_display.bottom - drop_display.top;
            if (master) {
                alternate = master->alternate_cd;
            }
            HWND scroll = CreateWindowExA(0, "Scrollbar", 0, 0x50010001, x, y, scrollbar_width, height, parent, 0,
                ProgramInstance, 0);
            data->attached_0c = scroll;
            data->scroll_width_04 = scrollbar_width;
            unknown_5ed180(scroll, 0);
            UnknownControlRecord *scroll_data = 0;
            unknown_registry_a73640.Get((unsigned int const &)data->attached_0c, scroll_data);
            scroll_data->owner_08 = window;
            scroll_data->alternate_cd = data->alternate_cd;
            UnknownScrollInfo info;
            info.nMax = max_top;
            info.fMask = 5;
            info.nMin = 0;
            info.nPos = data->unknown_f0;
            info.cbSize = 0x1c;
            SendMessageA(data->attached_0c, 0xe9, 0, (LPARAM)&info);
            SendMessageA(data->attached_0c, 0x4f1, 0, alternate);
            SetWindowPos(window, 0, 0, 0, drop_display.right - drop_display.left - scrollbar_width, drop_display.bottom - drop_display.top, 2);
            ShowWindow(data->attached_0c, 5);
            BringWindowToTop(data->attached_0c);
            InvalidateRect(data->attached_0c, 0, 0);
            UpdateWindow(data->attached_0c);
            SendMessageA(data->attached_0c, 0x4a9, (WPARAM)data->attached_0c, 1);
            SendMessageA(data->attached_0c, 0x4d2, 0, 1);
            RECT validate;
            validate.left = left;
            validate.top = top;
            validate.right = left + client.right + 1;
            validate.bottom = top + client.bottom + 1;
            ValidateRect(parent, &validate);
        }
    } else if (need_scrollbar == 0 && data && data->attached_0c && !data->unknown_20) {
        DestroyWindow(data->attached_0c);
        unknown_restore_child_5edd30(data->attached_0c, 0);
        data->attached_0c = 0;
        data->scroll_width_04 = 0;
        SetWindowPos(window, 0, 0, 0, client.right - client.left + scrollbar_width, client.bottom - client.top, 2);
        parent = GetParent(window);
        RECT validate_parent;
        Window_Rect_In_Main_Client(parent, &validate_parent);
        RECT validate;
        validate.left = rect.left - validate_parent.left;
        validate.top = rect.top - validate_parent.top;
        validate.right = validate.left + client.right + scrollbar_width;
        validate.bottom = validate.top + client.bottom + 1;
        ValidateRect(parent, &validate);
    }
    return DefWindowProcA(window, message, wparam, lparam);
}

}
