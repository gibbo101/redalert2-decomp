// unsigned short BitFontClass::Set_Color(unsigned short color) (0x00431430)
// Sets the packed text colour and returns the previous one. Re-plan of the
// accepted FontDrawState::ExchangeFontColor_00431430 (population-32) under
// the class text_print.hpp names.
#include "shared/text_print.hpp"

unsigned short BitFontClass::Set_Color(unsigned short color)
{
    unsigned short previous = Color;
    Color = color;
    return previous;
}
