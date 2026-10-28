// BitTextClass::BitTextClass() (0x00432290)
// Loads the game font.
#include "shared/text_print.hpp"
// @ref ??_7BitTextClass@@6B@=0079c790
// @ref ??2@YAPAXI@Z=00782017
// @ref ?BitFont@@3PAVBitFontClass@@A=0084e9e8
// @ref ??0BitFontClass@@QAE@PBD@Z=00431040
// @ref ??_C@_08KPFM@GAME?4FNT?$AA@=007cf540

BitTextClass::BitTextClass()
{
    BitFont = new BitFontClass("GAME.FNT");
}
