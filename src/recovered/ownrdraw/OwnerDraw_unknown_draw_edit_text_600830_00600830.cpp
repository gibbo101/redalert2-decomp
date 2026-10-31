// @ref ?unknown_color_a76150@OwnerDraw@@3HA=00a76150
// @ref ?unknown_color_a7338c@OwnerDraw@@3HA=00a7338c
// @ref ?Chars_In_Width@BitFontClass@@QBEHPBGHHH@Z=00431710
// @ref ?unknown_caret_hidden_a763ec@OwnerDraw@@3HA=00a763ec
#include "shared/win32_api.hpp"
#include "shared/surface.hpp"
#include "shared/text_print.hpp"
#include "shared/string_table.hpp"
#include "shared/win_stub.hpp"
#include "shared/owner_draw_dialog_control.hpp"

namespace OwnerDraw {

// Nonzero: do not draw the edit caret this time (cleared after every edit text draw; name hypothesis, 0x00A763EC).
extern int unknown_caret_hidden_a763ec;

// The larger of a and b (b when they are equal).
template<class T> inline T unknown_max(T a, T b) { return a < b ? b : a; }

// Draws an edit box's text in font at rect of surface, scrolled so the caret stays visible (*scroll is the
// first shown character). With ime the open IME composition is spliced in at the caret and drawn in the
// composition color; password shows '*' for every character; frame clears the text's background first.
// Each drawn run moves rect's left edge past it; the caret is drawn after the run that ends at it.
void __fastcall unknown_draw_edit_text_600830(Surface *surface, Rect &rect, wchar_t const *text, int caret,
                                              BitFontClass *font, unsigned int color, int *scroll, int ime,
                                              int password, int frame, int unknown9)
{
    wchar_t buffer[0x800];
    int caret_x = -1;
    int composition_length = 0;
    int composing = 0;
    if (text == 0) {
        text = L"";
    }
    int text_length = wcslen(text);
    if (caret < 0 || caret > text_length) {
        caret = 0;
    }
    if (ime) {
        IME_Update_Composition();
        composition_length = IMECompositionLength;
        composing = IMEComposing;
    }
    buffer[0] = 0;
    wcsncpy(buffer, text, 0x800);
    if (composition_length) {
        wcsncpy(&buffer[caret], IMECompositionString, 0x800 - caret);
        wcsncpy(&buffer[composition_length + caret], &text[caret], 0x800 - composition_length - caret);
    }
    buffer[0x7FF] = 0;
    int length = wcslen(buffer);
    if (password && length > 0) {
        wchar_t *p = buffer;
        for (int i = length; i != 0; i--) {
            *p++ = '*';
        }
    }
    int cursor;
    if (composing || composition_length) {
        cursor = IMECursorPosition + caret;
    } else {
        cursor = caret;
    }
    if (cursor < *scroll + 5) {
        if (cursor >= 5) {
            *scroll = cursor - 5;
        } else {
            *scroll = 0;
        }
    }
    while (*scroll < length) {
        if (font->Chars_In_Width(&buffer[*scroll], rect.Width - 5, 0, 0) >= cursor - *scroll) {
            break;
        }
        (*scroll)++;
    }
    int before = caret - *scroll;
    int lead = unknown_max(before, 0);
    int composed = composition_length;
    if (before < 0) {
        before += composition_length;
        composed = unknown_max(before, 0);
    }
    int after = length - composition_length - caret;
    if (before < 0) {
        after += before;
    }
    if (after < 0) {
        after = 0;
    }
    text = &buffer[*scroll];
    if (frame) {
        Rect area(rect.X - 1, rect.Y - 1, font->String_Pixel_Width(text, 0) + 5, rect.Height + 2);
        surface->Fill_Rect(area, 0);
    }
    if (lead) {
        int width = unknown_text_draw_005fe1b0(color, font, rect, text, lead, 0, 0, surface, unknown9);
        rect.X += width;
        rect.Width -= width;
        if (rect.Width < 0) {
            rect.Width = 0;
        }
        text += lead;
    }
    if (composed) {
        cursor -= *scroll + lead;
        int rest;
        if (cursor < 0 || cursor > composed) {
            rest = -1;
        } else {
            rest = composed - cursor;
            composed -= rest;
        }
        if (composed > 0) {
            int width = unknown_text_draw_005fe1b0(unknown_color_a76150, font, rect, text, composed, 0, 0, surface, unknown9);
            rect.X += width;
            rect.Width -= width;
            if (rect.Width < 0) {
                rect.Width = 0;
            }
            text += composed;
        }
        if (rest >= 0) {
            caret_x = rect.X;
            if (rest) {
                int width = unknown_text_draw_005fe1b0(unknown_color_a76150, font, rect, text, rest, 0, 0, surface, unknown9);
                rect.X += width;
                rect.Width -= width;
                if (rect.Width < 0) {
                    rect.Width = 0;
                }
                text += rest;
            }
        }
    } else {
        caret_x = rect.X;
    }
    if (after) {
        int width = unknown_text_draw_005fe1b0(color, font, rect, text, after, 0, 0, surface, unknown9);
        rect.X += width;
        rect.Width -= width;
        if (rect.Width < 0) {
            rect.Width = 0;
        }
    }
    if (ime && caret_x > 0 && !unknown_caret_hidden_a763ec) {
        unknown_draw_edge_glow_5fd290(surface, Point2D(caret_x, rect.Y), Point2D(caret_x, rect.Y + rect.Height - 2),
                                      unknown_color_a7338c, 0xFF);
        unknown_draw_edge_glow_5fd290(surface, Point2D(caret_x + 1, rect.Y), Point2D(caret_x + 1, rect.Y + rect.Height - 2),
                                      unknown_color_a7338c, 0xFF);
    }
    unknown_caret_hidden_a763ec = 0;
}

}
