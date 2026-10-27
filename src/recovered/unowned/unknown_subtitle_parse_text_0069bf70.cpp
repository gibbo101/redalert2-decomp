// void __fastcall unknown_subtitle_parse_text(wchar_t const *value, SubTitle *subtitle) -- 0x0069BF70
// Purpose: the "Text" handler of the subtitle script keyword table
// (0x007F62F8: Time, Duration, Position, Color, Text, each a wide name and
// a handler taking the value and the subtitle): sets the subtitle's text
// (0x0069B120).
// Assumptions: SubTitle is the RTTI-named element class of
// DynamicVectorClass<SubTitle *> (0x0069BF80); the setter's name and the
// handler signature are hypotheses.

class SubTitle {
public:
    void Set_Text(unsigned short const *text);     // 0x0069B120
};
// @ref ?Set_Text@SubTitle@@QAEXPBG@Z=0069b120

void __fastcall unknown_subtitle_parse_text(unsigned short const *value, SubTitle *subtitle)
{
    subtitle->Set_Text(value);
}
