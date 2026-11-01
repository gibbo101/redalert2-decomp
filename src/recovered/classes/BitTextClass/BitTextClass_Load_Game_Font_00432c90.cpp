// void BitTextClass::Load_Game_Font() (0x00432C90): loads GAME.FNT into BitFont, as the constructor. No callers.
#include "shared/text_print.hpp"

void BitTextClass::Load_Game_Font()
{
    BitFont = new BitFontClass("GAME.FNT");
}
