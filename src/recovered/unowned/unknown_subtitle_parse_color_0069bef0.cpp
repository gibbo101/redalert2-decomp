// void __fastcall unknown_subtitle_parse_color(wchar_t *value, SubTitle *subtitle) -- 0x0069BEF0
// Purpose: the "Color" handler of the subtitle script keyword table
// (0x007F62F8): parses "red:green:blue" (decimal, splitting the value in
// place at the colons) and sets the subtitle's colour (0x0069B100).
// Assumptions: as for the "Text" handler (0x0069BF70); the colour setter's
// name and byte parameters are hypotheses.

class SubTitle {
public:
    void Set_Color(unsigned char red, unsigned char green, unsigned char blue);    // 0x0069B100
};
// @ref ?Set_Color@SubTitle@@QAEXEEE@Z=0069b100

extern "C" unsigned short *__cdecl wcschr(unsigned short const *string, unsigned short character);   // 0x00783AC6
extern "C" unsigned long __cdecl wcstoul(unsigned short const *string, unsigned short **end, int base);   // 0x00784D76
// @ref _wcschr=00783ac6
// @ref _wcstoul=00784d76

void __fastcall unknown_subtitle_parse_color(unsigned short *value, SubTitle *subtitle)
{
    unsigned short *colon = wcschr(value, ':');
    *colon = 0;
    unsigned char red = (unsigned char)wcstoul(value, 0, 10);
    value = colon + 1;
    colon = wcschr(value, ':');
    *colon = 0;
    unsigned char green = (unsigned char)wcstoul(value, 0, 10);
    value = colon + 1;
    unsigned char blue = (unsigned char)wcstoul(value, 0, 10);
    subtitle->Set_Color(red, green, blue);
}
