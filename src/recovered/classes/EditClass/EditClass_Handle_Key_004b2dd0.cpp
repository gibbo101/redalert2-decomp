// bool EditClass::Handle_Key(int ascii) (0x004B2DD0, slot 38)
// Westwood's edit-key handling: 0 does nothing, backspace (8) removes the
// last character, return (13) drops the focus (and answers false); any
// other key that fits (pixel width and MaxLength) is appended when allowed
// by EditFlags (1 letters, 2 digits, 4 other printable characters,
// 8 upper-case letters); spaces always, but not as the first character.
#include "shared/gadget.hpp"
// @ref ?Font_For_Style@@YIPAVBitFontClass@@H@Z=00497a50
// @ref ?String_Pixel_Width@BitFontClass@@QBEHPBGH@Z=00431690
// @ref ?Char_Pixel_Width@BitFontClass@@QBEHG@Z=00432170
// @ref _isgraph=00782c8d
// @ref _isalpha=00782b0e
// @ref _toupper=007829d3
// @ref _isdigit=00782b8c
// @ref _isalnum=00782c31

extern "C" int __cdecl isgraph(int character);     // 0x00782C8D
extern "C" int __cdecl isalpha(int character);     // 0x00782B0E
extern "C" int __cdecl isdigit(int character);     // 0x00782B8C
extern "C" int __cdecl isalnum(int character);     // 0x00782C31
extern "C" int __cdecl toupper(int character);     // 0x007829D3

bool EditClass::Handle_Key(int ascii)
{
    BitFontClass *font = Font_For_Style(TextFlags);

    switch (ascii) {
    case 0:
        break;

    case 8:
        if (Length != 0) {
            Length--;
            String[Length] = 0;
            Flag_To_Redraw();
        }
        break;

    case 13:
        Clear_Focus();
        return false;

    default:
        if (font->String_Pixel_Width(String, 0) + font->Char_Pixel_Width(ascii) < Width - 2
            && (unsigned)Length < (unsigned)MaxLength) {
            if (!isgraph(ascii) && ascii != ' ') {
                break;
            }
            if (ascii == ' ' && Length == 0) {
                break;
            }
            if ((EditFlags & 8) && isalpha(ascii)) {
                ascii = toupper(ascii);
            }
            if ((!(EditFlags & 2) || !isdigit(ascii))
                && (!(EditFlags & 1) || !isalpha(ascii))
                && (!(EditFlags & 4) || isalnum(ascii))
                && ascii != ' ') {
                break;
            }
            String[Length++] = (wchar_t)ascii;
            String[Length] = 0;
            Flag_To_Redraw();
        }
        break;
    }
    return true;
}
