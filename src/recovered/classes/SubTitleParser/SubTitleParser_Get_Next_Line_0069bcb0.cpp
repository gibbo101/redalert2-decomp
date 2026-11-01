// unsigned short *SubTitleParser::Get_Next_Line() (0x0069BCB0): the next line that is not blank or a
// ';' comment, trimmed; 0 at the end of the input.
unsigned short *SubTitleParser::Get_Next_Line()
{
    bool eof = false;
    while (eof == false) {
        eof = Read_Line(Input, Buffer, 0x400);
        LineNumber++;
        unsigned short *string = wcstrim(Buffer);
        if (wcslen(string) > 0 && *string != ';') {
            return string;
        }
    }
    return 0;
}
