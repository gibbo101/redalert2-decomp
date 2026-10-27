// unsigned char BitFontClass::Set_Clipping(unsigned char clip) (0x00431450)
// Sets the raw clipping flag (not normalized to a truth value) and returns
// the previous one. Re-plan of the accepted
// FontDrawState::ExchangeFontClippingFlag_00431450 (population-32).
#include "shared/text_print.hpp"

unsigned char BitFontClass::Set_Clipping(unsigned char clip)
{
    unsigned char previous = Clipping;
    Clipping = clip;
    return previous;
}
