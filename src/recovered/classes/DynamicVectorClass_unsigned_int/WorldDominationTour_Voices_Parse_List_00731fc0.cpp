// void __fastcall WorldDominationTour::Voices::Parse_List(Wstring const &text, DynamicVectorClass<unsigned> &lines) (0x00731FC0)
// Replaces lines with the comma separated numbers of text.
#include "shared/wdt_voices.hpp"

namespace WorldDominationTour {

void __fastcall Voices::Parse_List(Wstring const &text, DynamicVectorClass<unsigned> &lines)
{
    lines.Clear();
    Wstring token;
    int position = text.Get_Token(0, ",", token);
    while (position != -1) {
        lines.Add(token.As_Integer());
        position = text.Get_Token(position, ",", token);
    }
}

}
