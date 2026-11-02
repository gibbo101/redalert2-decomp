// int __fastcall unknown_hex_value_412390(char const *text) (0x00412390)
// The value of the hexadecimal digits at the start of text (0 for none or no text; called by the
// trigger and team readers 0x006B49B6, 0x006B6CD5).
// @ref _isxdigit=00782bb4
// @ref _toupper=007829d3
extern "C" int __cdecl isxdigit(int c);
extern "C" int __cdecl toupper(int c);

int __fastcall unknown_hex_value_412390(char const *text)
{
    int value = 0;
    while (text != 0 && isxdigit(*text)) {
        char c = *text;
        value <<= 4;
        text++;
        if (c >= '0' && c <= '9') {
            value += c - '0';
        } else {
            value += toupper(c) - 'A' + 10;
        }
    }
    return value;
}
