// unsigned __fastcall unknown_parse_timecode(unsigned short const *text) -- 0x0069BD60
// Purpose: parses a wide "H:M:S:F" time code (the first 11 characters) and
// returns ((H * 60 + M) * 60 + S) * 60 plus F scaled from hundredths to
// sixtieths.
// Assumptions: the three CRT calls are wcsncpy (0x00783622), wcschr
// (0x00783AC6) and wcstol (0x00784D76) on 16-bit characters; the name is
// a hypothesis.
// @ref _wcsncpy=00783622
// @ref _wcschr=00783ac6
// @ref _wcstol=00784d76
extern "C" unsigned short *__cdecl wcsncpy(unsigned short *dest, unsigned short const *source, unsigned int count);
extern "C" unsigned short *__cdecl wcschr(unsigned short const *text, unsigned short character);
extern "C" long __cdecl wcstol(unsigned short const *text, unsigned short **end, int base);

unsigned __fastcall unknown_parse_timecode(unsigned short const *text)
{
    unsigned short buffer[12];
    wcsncpy(buffer, text, 12);
    buffer[11] = 0;
    unsigned short *colon1 = wcschr(buffer, ':');
    *colon1 = 0;
    int hours = wcstol(buffer, 0, 10);
    unsigned short *colon2 = wcschr(colon1 + 1, ':');
    *colon2 = 0;
    int minutes = wcstol(colon1 + 1, 0, 10);
    unsigned short *colon3 = wcschr(colon2 + 1, ':');
    *colon3 = 0;
    int seconds = wcstol(colon2 + 1, 0, 10);
    int frames = wcstol(colon3 + 1, 0, 10);
    return (unsigned)(frames * 60) / 100 + (seconds + (minutes + hours * 60) * 60) * 60;
}
