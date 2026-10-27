// Exact original0x00413770; 54 body bytes plus frozen full NOP gap.
// Observed ABI projection; original game class and developer prototype unknown.
#include "shared/integer_coordinate_views.hpp"

SignedWordPair* Div256PairSource_00413770::CopyDiv256PairAsSignedWords_00413770(SignedWordPair* output) const
{
    SignedWordPair result;
    result.x = (short)(x / 256);
    result.y = (short)(y / 256);
    *output = result;
    return output;
}
