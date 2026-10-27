// int ScoreFontClass::String_Pixel_Width(wchar_t const *string) -- 0x00667A60 (slot 2)
// Purpose: the width of a string: each character's width (slot 1,
// 0x00667AA0; a space is 8) plus one pixel of spacing.
// Assumptions: ScoreFontClass (RTTI vtable 0x007A92A0, five slots, no
// fields used here) is declared only as far as needed; names hypotheses.

class ScoreFontClass {
public:
    virtual ~ScoreFontClass();                                      // slot 0 (0x006683D0)
    virtual int Char_Pixel_Width(unsigned short character);         // slot 1 0x00667AA0
    virtual int String_Pixel_Width(unsigned short const *string);   // slot 2 0x00667A60
};

int ScoreFontClass::String_Pixel_Width(unsigned short const *string)
{
    int width = 0;
    while (*string != 0) {
        width += Char_Pixel_Width(*string++) + 1;
    }
    return width;
}
