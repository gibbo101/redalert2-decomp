// MSAnimEntry::MSAnimEntry(Wstring const &line) (0x005B14C0)
// Parses "name,a,b,c".
#include "shared/ms_choice.hpp"
// @ref ??_C@_01KMAE@?0?$AA@=007ce9c0
// @ref ?As_Integer@Wstring@@QBEHXZ=0076f570
// @ref ?Get_Token@Wstring@@QBEHHPBDAAV1@@Z=0076f200

MSAnimEntry::MSAnimEntry(Wstring const &line) :
    Name((char const *)0),
    unknown_04(0),
    unknown_08(0),
    unknown_0C(0)
{
    Wstring token;
    int position = line.Get_Token(0, ",", token);
    if (token.Length() > 0) {
        Name = token;
    }
    position = line.Get_Token(position, ",", token);
    if (token.Length() > 0) {
        unknown_04 = token.As_Integer();
    }
    position = line.Get_Token(position, ",", token);
    if (token.Length() > 0) {
        unknown_08 = token.As_Integer();
    }
    line.Get_Token(position, ",", token);
    if (token.Length() > 0) {
        unknown_0C = token.As_Integer();
    }
}
