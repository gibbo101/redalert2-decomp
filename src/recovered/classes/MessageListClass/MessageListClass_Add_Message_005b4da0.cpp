// MessageListClass::Add_Message -- 0x005B4DA0
#include "shared/text_label.hpp"
#include "shared/message_list.hpp"
#include "shared/text_print.hpp"
#include "shared/comm_buffer.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/crt_memory.hpp"
#include "shared/rules.hpp"
#include "shared/sound_play.hpp"
extern "C" unsigned int __cdecl wcslen(unsigned short const *string);
extern "C" unsigned short *__cdecl wcscpy(unsigned short *dest, unsigned short const *source);
extern "C" unsigned short *__cdecl wcscat(unsigned short *dest, unsigned short const *source);
extern "C" unsigned short *__cdecl wcsncat(unsigned short *dest, unsigned short const *source, unsigned int count);
extern unsigned short const unknown_prefix_separator_7e5e0c[];
// @ref ?unknown_prefix_separator_7e5e0c@@3QBGB=007e5e0c
// @ref _wcsncat=00784704
// @ref ?unknown_flag_a3f209@@3_NA=00a3f209
// @ref ?unknown_flag_a3f208@@3_NA=00a3f208

TextLabelClass *MessageListClass::Add_Message(unsigned short const *prefix, int identifier,
    unsigned short const *text, int color, unsigned style, int delay, bool unknown_flag)
{
    BitFontClass *font = Font_For_Style(style);
    if (text == 0) return 0;
    if (font == 0) return 0;
    unsigned short message[162];
    message[0] = 0;
    if (prefix != 0) {
        wcscpy(message, prefix);
        wcscat(message, unknown_prefix_separator_7e5e0c);
    }
    int prefix_length = wcslen(message);
    int prefix_width = font->String_Pixel_Width((wchar_t const *)message, 0);
    int text_length = wcslen(text);
    int width = TextWidth - prefix_width - 8;
    if (width <= 0) return 0;
    int chars = font->Chars_In_Width((wchar_t const *)text, width, 111, 1);
    if (chars < 0) return 0;
    wcsncat(message, text, chars);
    message[prefix_length + chars] = 0;
    if (MaxMessages > 0 && Num_Messages() + 1 > MaxMessages) {
        TextLabelClass *old = First;
        if (old == 0) return 0;
        First = (TextLabelClass *)old->Remove();
        for (int slot = 0; slot < 14; slot++) {
            if (old->Text == (wchar_t const *)Texts[slot]) Slot_Free[slot] = 1;
        }
        delete old;
    }
    TextLabelClass *label = new TextLabelClass((wchar_t const *)message, X, Y, color, style | 0x8000);
    if (unknown_game_mode_a3d298 == 4) {
        label->IsRevealed = !unknown_flag && unknown_flag_a3f209;
    } else if (unknown_game_mode_a3d298 == 3) {
        label->IsRevealed = !unknown_flag && unknown_flag_a3f208;
    } else {
        label->IsRevealed = !unknown_flag;
    }
    if (delay == -1) label->UserData1 = 0;
    else label->UserData1 = TickCount.Time() + delay;
    label->UserData2 = identifier;
    label->PixWidth = TextWidth;
    int found = 0;
    for (int i = 0; i < 14; i++) {
        if (Slot_Free[i]) {
            Slot_Free[i] = 0;
            memset(Texts[i], 0, 162);
            wcscpy(Texts[i], message);
            label->Text = (wchar_t const *)Texts[i];
            found = 1;
            break;
        }
    }
    if (!found) {
        delete label;
        return 0;
    }
    if (!unknown_flag) Voc_Play(Rules->IncomingMessage, 1.0f, 0x2000, 0);
    if (First) label->Add_Tail(*First);
    else First = label;
    int y;
    if (IsEdit && AdjustEdit) y = Height + Y;
    else y = Y;
    TextLabelClass *node = First;
    while (node) {
        node->Y = y;
        node = (TextLabelClass *)node->Get_Next();
        y += Height;
    }
    if (chars < text_length) {
        unsigned short const *remaining = text + chars;
        while (*remaining != 0 && *remaining < 0x20) remaining++;
        if (*remaining != 0) Add_Message(prefix, identifier, remaining, color, style, delay, true);
    }
    return label;
}
