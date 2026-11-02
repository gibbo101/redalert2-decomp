// MessageListClass::Concat_Message (0x005B51C0): append to a matching live message.
// Appends text to the message with this identifier and prefix, trimming the front of the message when it would
// no longer fit, and renews its expiry.
// @ref ?Font_For_Style@@YIPAVBitFontClass@@H@Z=00497a50
// @ref ?String_Pixel_Width@BitFontClass@@QBEHPB_WH@Z=00431690
// @ref _wcslen=00783605
// @ref _wcscpy=00783689
// @ref _wcscat=0078365f
// @ref ?Trim_Message@MessageListClass@@QAEHPAG0HHH@Z=005b5cb0
// @ref ?TickCount@@3V?$TTimerClass@VSystemTimerClass@@@@A=00839980
#include "shared/text_label.hpp"
#include "shared/message_list.hpp"
#include "shared/message_gadget_layout.hpp"
#include "shared/text_print.hpp"
#include "shared/comm_buffer.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/crt_memory.hpp"
extern "C" unsigned int __cdecl wcslen(unsigned short const *string);
extern "C" unsigned short *__cdecl wcscpy(unsigned short *dest, unsigned short const *source);
extern "C" unsigned short *__cdecl wcscat(unsigned short *dest, unsigned short const *source);

int MessageListClass::Concat_Message(unsigned short const *prefix, int identifier, unsigned short const *text, int delay)
{
    if (prefix == 0 || text == 0 || !unknown_18) return 0;
    TextLabelClass *node = 0;
    int found = 0;
    if (First) {
        node = First;
        while (node) {
            if (node->UserData2 == identifier && memcmp(node->Text, prefix, wcslen(prefix) * 2) == 0) {
                found = 1;
                break;
            }
            node = (TextLabelClass *)node->Get_Next();
        }
    }
    if (!found) return 0;
    unsigned short *tail = (unsigned short *)node->Text + wcslen(prefix) + 1;
    unsigned int max = MaxChars;
    if (wcslen(tail) + wcslen(text) < max) {
        unsigned short *buffer = (unsigned short *)operator new(max * 2 + 2);
        BitFontClass *font = Font_For_Style(node->Style);
        int extra = font->String_Pixel_Width(node->Text, 0) - font->String_Pixel_Width((wchar_t const *)tail, 0);
        wcscpy(buffer, tail);
        wcscat(buffer, text);
        while (font->String_Pixel_Width((wchar_t const *)buffer, 0) + extra >= TextWidth) {
            int length = wcslen(tail);
            if (length < 10) {
                length = 10;
            }
            Trim_Message(0, tail, 10, length, 0);
            wcscpy(buffer, tail);
            wcscat(buffer, text);
        }
        delete buffer;
        wcscat(tail, text);
    } else {
        int length = wcslen(tail) - MaxChars + wcslen(text);
        int most = wcslen(tail);
        if (most < length) {
            most = length;
        }
        Trim_Message(0, tail, length, most, 0);
        wcscat(tail, text);
    }
    if (delay == -1) {
        node->UserData1 = 0;
        return 1;
    }
    node->UserData1 = TickCount.Time() + delay;
    return 1;
}
