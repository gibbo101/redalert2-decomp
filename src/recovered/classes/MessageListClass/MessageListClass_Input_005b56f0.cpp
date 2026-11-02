// int MessageListClass::Input(int &input, unsigned short key) -- 0x005B56F0
// The edit line's input: a mouse click (with the right button) closes it; Escape closes it, Return closes it
// (sent when it holds text, which gets a trailing space), Backspace removes the last character, and other
// printable characters are added while there is room (MaxChars and the pixel width); with unknown_18 set
// a full line moves its start to OverflowBuf. Keys without a character come through WWKeyboard.
// @ref ?To_Char@WWKeyboardClass@@QAEDG@Z=00532800
// @ref ?WWKeyboard@@3PAVWWKeyboardClass@@A=00832468
// @ref ?Font_For_Style@@YIPAVBitFontClass@@H@Z=00497a50
// @ref ?String_Pixel_Width@BitFontClass@@QBEHPB_WH@Z=00431690
// @ref ?Unknown_00738100@@YAXXZ=00738100
#include "shared/text_label.hpp"
#include "shared/message_list.hpp"
#include "shared/text_print.hpp"
#include "shared/keyboard.hpp"

int MessageListClass::Input(int &input, unsigned short key)
{
    int retcode = 0;
    if (key == 0) {
        if (input == 0) {
            return 0;
        }
        int button = input & ~0x800;
        if (button == 1 || button == 2) {
            if ((input & 2) && IsEdit) {
                Remove_Edit();
                return 2;
            }
            return 0;
        }
    }
    if (IsEdit) {
        int ascii;
        if (key == 0) {
            ascii = WWKeyboard->To_Char((KeyNumType)input) & 0xff;
            if ((input & 0x1000) && ascii >= '0' && ascii <= '9') {
                input &= ~0x1000;
            } else if ((!(input & 0x1000) && !(input & 0x8000) && ascii >= ' ') || (input & 0xff) == 13
                || (input & 0xff) == 8 || (input & 0xff) == 27) {
            } else {
                input = 0;
                return 0;
            }
        } else {
            ascii = key;
        }
        switch (ascii) {
        case 27:
            Remove_Edit();
            retcode = 2;
            input = 0;
            break;
        case 13:
            if (EditCurPos < EditInitPos) {
                EditCurPos = EditInitPos;
            }
            while (EditBuf[EditCurPos] != 0 && EditCurPos - EditInitPos < MaxChars - 1) {
                EditCurPos++;
            }
            if (EditCurPos == EditInitPos) {
                Remove_Edit();
                retcode = 2;
                input = 0;
                break;
            }
            if (EditCurPos - EditInitPos < MaxChars - 1) {
                EditBuf[EditCurPos] = ' ';
                EditCurPos++;
                EditBuf[EditCurPos] = 0;
            }
            Remove_Edit();
            retcode = 3;
            input = 0;
            break;
        case 8:
            if (EditCurPos > EditInitPos) {
                EditCurPos--;
                EditBuf[EditCurPos] = 0;
                retcode = 2;
            }
            input = 0;
            EditLabel->Set_Focus();
            break;
        default:
            EditLabel->Set_Focus();
            if (ascii > 0x1f && ascii < 0x10000) {
                bool overflow = false;
                while (EditBuf[EditCurPos] != 0 && EditCurPos - EditInitPos < MaxChars - 1) {
                    EditCurPos++;
                }
                if (EditCurPos - EditInitPos < MaxChars - 1) {
                    EditBuf[EditCurPos] = ascii;
                    EditCurPos++;
                    EditBuf[EditCurPos] = 0;
                    retcode = 1;
                    BitFontClass *font = Font_For_Style(EditLabel->Style);
                    if (font->String_Pixel_Width((wchar_t const *)EditBuf, 0) >= TextWidth - 10) {
                        EditCurPos--;
                        EditBuf[EditCurPos] = 0;
                        overflow = true;
                    }
                } else {
                    overflow = true;
                }
                if (overflow) {
                    if (unknown_18) {
                        int count = Trim_Message(OverflowBuf, &EditBuf[EditInitPos], Selection_First, Selection_Last, 1);
                        EditCurPos -= count;
                        EditBuf[EditCurPos] = ascii;
                        EditCurPos++;
                        EditBuf[EditCurPos] = 0;
                        retcode = 4;
                    } else {
                        retcode = 0;
                    }
                }
            }
            input = 0;
            break;
        }
    }
    return retcode;
}
