// bool SubTitleParser::Parse_Sub_Title(unsigned short *string, SubTitle *subtitle) (0x0069BAD0): the
// entry's "token = value" pairs (values quoted or up to a comma or blank), each passed to its handler.
// @ref ??_C@_15MHMA@?$AA?0?$AA?5?$AA?$AA@=007f6520
// @ref ??_C@_11A@?$AA?$AA@=00839d4c
// @ref ??_C@_0CA@EAIC@Error?5on?5line?5?$CFd?3?5syntax?5error?6?$AA@=007f6500
// @ref ??_C@_0CF@FPAI@Error?5on?5line?5?$CFd?3?5mismatched?5quo@=007f64d8
// @ref ??_C@_0CB@CJH@Error?5on?5line?5?$CFd?3?5missing?5token?6@=007f64b4
bool SubTitleParser::Parse_Sub_Title(unsigned short *string, SubTitle *subtitle)
{
    for (;;) {
        unsigned short *separator = wcschr(string, '=');
        if (separator == 0) {
            Debug_Printf("Error on line %d: syntax error\n", LineNumber);
            return false;
        }
        *separator = 0;
        unsigned short *token = string;
        wcstrim(token);
        unsigned short *param = separator + 1;
        wcstrim(param);
        if (*param == '"') {
            param++;
            unsigned short *ptr = wcschr(param, '"');
            if (ptr == 0) {
                Debug_Printf("Error on line %d: mismatched quotes\n", LineNumber);
                return false;
            }
            *ptr++ = 0;
            wcstrim(ptr);
            if (*ptr == ',') {
                ptr++;
            }
            string = ptr;
        } else {
            unsigned short *ptr = wcspbrk(param, L", ");
            if (ptr != 0) {
                *ptr = 0;
                string = ptr + 1;
            } else {
                string = L"";
            }
        }
        if (wcslen(token) == 0) {
            Debug_Printf("Error on line %d: missing token\n", LineNumber);
            return false;
        }
        Parse_Token(token, param, subtitle);
        wcstrim(string);
        if (wcslen(string) == 0) {
            return true;
        }
    }
}
