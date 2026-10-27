// MSTextEntry::MSTextEntry(WideString const &line) (0x005B13D0)
// Parses "x,y,unknown,text".
#include "shared/ms_choice.hpp"
// @ref ??_C@_13JKDK@?$AA?0?$AA?$AA@=007e5c64
// @ref ??0WideString@@QAE@PBG@Z=0076f9c0
// @ref ??0WideString@@QAE@XZ=0076f9b0
// @ref ??1WideString@@QAE@XZ=0076fa50
// @ref ??4WideString@@QAEAAV0@ABV0@@Z=0076fbd0
// @ref ?As_Integer@WideString@@QBEHXZ=00771070
// @ref ?Get_Token@WideString@@QBEHHPBGAAV1@@Z=00770d50
// @ref ?Length@WideString@@QBEIXZ=007704a0

MSTextEntry::MSTextEntry(WideString const &line) :
    X(0),
    Y(0),
    unknown_08(0),
    Text((unsigned short const *)0)
{
    WideString token;
    int position = line.Get_Token(0, L",", token);
    if (token.Length() > 0) {
        X = token.As_Integer();
    }
    position = line.Get_Token(position, L",", token);
    if (token.Length() > 0) {
        Y = token.As_Integer();
    }
    position = line.Get_Token(position, L",", token);
    if (token.Length() > 0) {
        unknown_08 = token.As_Integer();
    }
    line.Get_Token(position, L",", token);
    if (token.Length() > 0) {
        Text = token;
    }
}
