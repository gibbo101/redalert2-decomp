// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright 2026 ra2-decomp contributors
// Copyright 2025 Electronic Arts Inc.; 2026 OpenTS contributors
// Derived from Electronic Arts source code; EA's GPL Section 7 terms apply (COPYING.md).
// LRESULT OwnerDraw::unknown_trackbar_proc_5fb270(HWND, UINT, WPARAM, LPARAM) (0x005FB270)
// Adopted from ra2-decomp OwnerDraw::TrackBarHandler (YR 0x0061D950).
// @ref ?unknown_surface_839958@@3PAVSurface@@A=00839958
// @ref ?Window_Rect_In_Main_Client@@YIHPAUHWND__@@PAURECT@@@Z=00735690
// @ref ?unknown_registry_a73640@OwnerDraw@@3VUnknownControlIndex@1@A=00a73640
// @ref ?unknown_window_procs_a73688@OwnerDraw@@3VUnknownWindowProcIndex@1@A=00a73688
// @ref ?unknown_surface_count_a763d8@OwnerDraw@@3HA=00a763d8
// @ref ?unknown_bitmap_writer_a76378@@3VUnknownBitmapWriter@@A=00a76378
// @ref ?Get_Image_0068ca40@UnknownBitmapWriter@@QAEPAVSurface@@PBDH@Z=0068ca40
// @ref ?Draw_0068cce0@UnknownBitmapWriter@@QAE_NABVRect@@PAVSurface@@1HH@Z=0068cce0
// @ref ?Unknown_005feb60@@YIXPAVRect@@PAVSurface@@HH@Z=005feb60
// @ref ?unknown_5fdb20@OwnerDraw@@YIXPAVSurface@@ABVRect@@HH@Z=005fdb20
// @ref ?unknown_draw_text_5fe020@OwnerDraw@@YIHPAVSurface@@PBGPAURECT@@PAVBitFontClass@@KHHHHH@Z=005fe020
// @ref ?unknown_color_a76158@OwnerDraw@@3HA=00a76158
// @ref ?unknown_color_a737e0@OwnerDraw@@3HA=00a737e0
// @ref ?unknown_color_a763b8@OwnerDraw@@3HA=00a763b8
// @ref ?unknown_color_a733e4@OwnerDraw@@3HA=00a733e4
// @ref ?unknown_color_a737ec@OwnerDraw@@3HA=00a737ec
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?Voc_Play@@YIPAUAudioEvent@@HMHPAUAudioEventHandle@@@Z=00713db0
// @ref _swprintf=00783764
// @ref ??_C@_15KLDP@?$AA?$CF?$AAd?$AA?$AA@=007d1598
// @ref ??_C@_09FKJE@trofm?4pcx?$AA@=007eaf80
// @ref ??_C@_09PKLB@trofl?4pcx?$AA@=007eaf74
// @ref ??_C@_09DJBB@trofr?4pcx?$AA@=007eaf68
// @ref ??_C@_0N@EK@trakgrip?4pcx?$AA@=007eaf58
// @ref ??_7BSurface@@6B@=0079aef8
// @ref ??_7XSurface@@6B@=0079af8c
// @ref ??0Buffer@@QAE@PAXJ@Z=004382c0
// @ref ??2@YAPAXI@Z=00782017
// @ref __imp__CallWindowProcA@20=0079a4c0
// @ref __imp__ValidateRect@8=0079a3f8
#include "shared/unknown_globals.hpp"
#include "shared/win32_api.hpp"
#include "shared/win32_window.hpp"
#include "shared/surface.hpp"
#include "shared/pcx_cache.hpp"
#include "shared/rules.hpp"
#include "shared/sound_play.hpp"
#include "shared/string_table.hpp"
#include "shared/owner_draw_dialog_control.hpp"

namespace OwnerDraw {

// A track bar's state in its registry record from +0xE8 (the progress bar keeps its range there).
struct UnknownTrackBarState {
    int result;         // +0xE8
    int dragging;       // +0xEC
    int range;          // +0xF0
    int value;          // +0xF4
    int minimum;        // +0xF8
    int thumb_pos;      // +0xFC
    int step;           // +0x100
    int show_numbers;   // +0x104
    int click_suppress; // +0x108
};

// The window procedure of the msctls_trackbar32 controls.
LRESULT __stdcall unknown_trackbar_proc_5fb270(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
{
    bool play_click = true;

    RECT client_rect;
    RECT display_rect;
    GetClientRect(window, &client_rect);
    Window_Rect_In_Main_Client(window, &display_rect);
    int number_width = 50;

    UnknownControlRecord *data = Get_Record(window);
    if (data == 0) {
        return 0;
    }
    UnknownTrackBarState *track = (UnknownTrackBarState *)&data->unknown_e8;

    int message_result = track->result;
    int dragging = track->dragging;
    int maximum;
    int thumb_pos = track->thumb_pos;
    int range = track->range;
    int value = track->value;
    int minimum = track->minimum;
    int step = track->step;
    int show_numbers = track->show_numbers;

    if (!show_numbers) {
        number_width = 0;
    }

    int slider_width = client_rect.right - client_rect.left - number_width - 13;
    if (slider_width <= 1) {
        slider_width = 1;
    }

    if (!range) {
        WNDPROC proc = 0;
        WNDPROC *found = 0;
        if (unknown_window_procs_a73688.Get(window, found) && found) {
            proc = *found;
        }

        int range_max = CallWindowProcA(proc, window, 0x402, 0, 0);
        minimum = CallWindowProcA(proc, window, 0x401, 0, 0);
        range = range_max - minimum;
        value = CallWindowProcA(proc, window, 0x400, 0, 0) - minimum;
        thumb_pos = value * slider_width / range;
        if (!range) {
            range = 100;
        }

        track->thumb_pos = thumb_pos;
        track->range = range;
        track->value = value;
        track->minimum = minimum;
        track->step = step;
        track->show_numbers = show_numbers;
    }

    if (!step) {
        number_width = 50;
        step = 1;
        show_numbers = 1;
    }

    LONG grip_left;
    LONG grip_right;
    if (!dragging) {
        grip_left = client_rect.left + thumb_pos + 1;
        grip_right = grip_left + 12;
    } else {
        POINT point;
        GetCursorPos(&point);
        ScreenToClient(window, &point);

        int xpos = point.x - 6;
        if (xpos < 1) {
            xpos = 1;
        }
        if (client_rect.right - number_width - 12 < xpos) {
            xpos = client_rect.right - number_width - 12;
        }

        int idx = ((range + 1) * (xpos - 1)) / slider_width;
        if (idx >= range) {
            idx = range;
        }

        value = step * ((minimum + idx) / step) - minimum;
        thumb_pos = value * slider_width / range;
        grip_left = thumb_pos + 1;
        grip_right = grip_left + 12;
    }

    switch (message) {
    case 0x84:
    case 0x87: {
        WNDPROC proc = 0;
        WNDPROC *found = 0;
        if (unknown_window_procs_a73688.Get(window, found) && found) {
            proc = *found;
        }
        return CallWindowProcA(proc, window, message, wparam, lparam);
    }

    case 0xa:
        InvalidateRect(window, 0, FALSE);
        break;

    case 0xf: {
        RECT paint_rect;
        Window_Rect_In_Main_Client(window, &paint_rect);
        Rect disp_rect(paint_rect.left, paint_rect.top, paint_rect.right - paint_rect.left, paint_rect.bottom - paint_rect.top);
        LONG style = GetWindowLongA(window, -16);

        if (data->surface_10 == 0) {
            RECT disp_copy;
            RECT client_copy;
            Window_Rect_In_Main_Client(window, &disp_copy);
            GetClientRect(window, &client_copy);

            Surface *surf = new BSurface(client_copy.right + 1, client_copy.bottom + 1, 2);
            data->surface_10 = surf;
            unknown_surface_count_a763d8++;

            Rect src_rect(0, 0, client_copy.right + 1, client_copy.bottom + 1);
            Rect dst_rect(disp_copy.left, disp_copy.top, client_copy.right + 1, client_copy.bottom + 1);
            surf->Copy_From(src_rect, *unknown_surface_839958, dst_rect, false, true);
            Unknown_005feb60(&src_rect, surf, 0, data->unknown_c8);
        }

        if (data->surface_10 != 0) {
            RECT disp_copy;
            RECT client_copy;
            Window_Rect_In_Main_Client(window, &disp_copy);
            GetClientRect(window, &client_copy);

            Rect src_rect(0, 0, client_copy.right + 1, client_copy.bottom + 1);
            Rect dst_rect(disp_copy.left, disp_copy.top, client_copy.right + 1, client_copy.bottom + 1);
            unknown_surface_839958->Copy_From(dst_rect, *data->surface_10, src_rect, false, true);
        }

        if (show_numbers) {
            {
                Surface *center = unknown_bitmap_writer_a76378.Get_Image_0068ca40("trofm.pcx", 0);
                Rect center_rect(disp_rect.X + disp_rect.Width - number_width + 1, disp_rect.Y - 1, number_width, center->Get_Height());
                unknown_bitmap_writer_a76378.Draw_0068cce0(center_rect, unknown_surface_839958, center, 0, 0);
            }
            {
                Surface *left = unknown_bitmap_writer_a76378.Get_Image_0068ca40("trofl.pcx", 0);
                Rect left_dst(disp_rect.X + disp_rect.Width - number_width + 1, disp_rect.Y - 1, left->Get_Width(), left->Get_Height());
                Rect left_src = left_dst;
                left_src.Y = 0;
                left_src.X = 0;
                unknown_surface_839958->Copy_From(left_dst, *left, left_src, false, true);
            }
            {
                Surface *right = unknown_bitmap_writer_a76378.Get_Image_0068ca40("trofr.pcx", 0);
                Rect right_dst(disp_rect.X + disp_rect.Width - right->Get_Width() + 1, disp_rect.Y - 1, right->Get_Width(), right->Get_Height());
                Rect right_src = right_dst;
                right_src.Y = 0;
                right_src.X = 0;

                unknown_surface_839958->Copy_From(right_dst, *right, right_src, false, true);
            }
        }

        Rect grip_rect(paint_rect.left + grip_left, paint_rect.top, grip_right - grip_left, paint_rect.bottom - paint_rect.top);
        Surface *grip = unknown_bitmap_writer_a76378.Get_Image_0068ca40("trakgrip.pcx", 0);
        Rect grip_src;
        grip_src.X = 0;
        grip_src.Y = 0;
        grip_src.Width = grip->Get_Width();
        grip_src.Height = grip->Get_Height();
        unknown_surface_839958->Copy_From(grip_rect, *grip, grip_src, false, true);

        int disabled = style & 0x8000000;
        if (disabled) {
            Unknown_005feb60(&grip_rect, unknown_surface_839958, 0, unknown_color_a763b8);
        }

        int frame_color = unknown_5fda40(unknown_color_a76158);
        if (disabled) {
            frame_color = unknown_5fda40(unknown_color_a737e0);
        }

        Rect frame_rect = disp_rect;
        frame_rect.Width = disp_rect.Width - number_width;
        unknown_5fdb20(unknown_surface_839958, frame_rect, 1, frame_color);

        Rect number_rect = disp_rect;
        int inset = (show_numbers != 0) + 1;
        number_rect.X = inset - number_width + disp_rect.Width + disp_rect.X;
        number_rect.Width = number_width - inset;
        unknown_5fdb20(unknown_surface_839958, number_rect, 1, frame_color);

        if (show_numbers) {
            wchar_t buffer[32];


            swprintf(buffer, L"%d", step * ((minimum + value) / step));

            int text_color = unknown_color_a733e4;
            if (disabled) {
                text_color = unknown_color_a737ec;
            }

            RECT text_rect = paint_rect;
            text_rect.left = paint_rect.right - 49;
            unknown_draw_text_5fe020(unknown_surface_839958, buffer, &text_rect, data->font_64, text_color, 5, 0xc, 0, 0, 0);
        }

        ValidateRect(window, 0);
        break;
    }

    case 0x14:
        return 0;

    case 0x200:
        if (dragging) {
            RECT rect = client_rect;
            InvalidateRect(window, &rect, FALSE);
        }
        if (wparam & 1) {
            break;
        }

    case 0x202:
        message_result = 0;
        dragging = 0;
        ReleaseCapture();
        break;

    case 0x201:
    case 0x203: {
        if (message == 0x201) {
            message_result = 1;
            SetCapture(window);
        } else {
            message_result = 0;
            ReleaseCapture();
        }

        int xpos = (unsigned short)lparam;
        int ypos = (unsigned short)((unsigned int)lparam >> 16);
        if (ypos > client_rect.bottom - 18) {
            if (xpos >= grip_left && xpos < grip_right) {
                if (message == 0x201) {
                    dragging = 1;
                }
            } else {
                int x = xpos - 6;
                if (x < 1) {
                    x = 1;
                }
                if (client_rect.right - number_width - 12 < x) {
                    x = client_rect.right - number_width - 12;
                }


                int idx = ((range + 1) * (x - 1)) / slider_width;
                if (idx >= range) {
                    idx = range;
                }

                value = step * ((minimum + idx) / step) - minimum;
                thumb_pos = value * slider_width / range;
            }
        }
        break;
    }

    case 0x400:
        return step * ((minimum + value) / step);

    case 0x405:
        if (lparam - minimum <= range && lparam - minimum >= 0) {
            value = lparam - minimum;
        }
        play_click = false;
        thumb_pos = value * slider_width / range;
        break;

    case 0x406:
        minimum = (unsigned short)lparam;
        maximum = (unsigned short)((unsigned int)lparam >> 16);
        range = maximum - minimum;
        if (value > range) {
            value = range;
        }
        if (value < minimum) {
            value = minimum;
        }
        play_click = false;
        thumb_pos = value * slider_width / range;
        break;

    case 0x4ab:
        step = lparam;
        break;

    case 0x4ac:
        show_numbers = lparam;
        break;

    case 0x4ae:
        track->click_suppress = (wparam == 0);
        break;
    }

    int changed = 0;
    if (value != track->value || range != track->range || minimum != track->minimum) {
        changed = 1;
    }

    track->result = message_result;
    track->dragging = dragging;
    track->thumb_pos = thumb_pos;
    track->range = range;
    track->value = value;
    track->minimum = minimum;
    track->step = step;
    track->show_numbers = show_numbers;

    if (changed) {
        InvalidateRect(window, 0, FALSE);

        HWND parent = GetParent(window);
        SendMessageA(parent, 0x114, (WPARAM)((unsigned short)5 | (unsigned long)(unsigned short)(value + minimum) << 16), (LPARAM)window);

        if (play_click == true && !track->click_suppress) {
            Voc_Play(Rules->unknown_62c, 1.0f, 0x2000, 0);
        }
    }

    return 0;
}

}
