// wchar_t const *TauntCommandClass::Get_Description() const -- 0x0051B5C0
// The localized description (TXT_TAUNT_DESC) formatted with the taunt number
// into the shared command text buffer (0x00A4153C).
#include "shared/command.hpp"
// @ref ?Load_String@StringTable@@SIPBGPBDPAD0H@Z=006f9ec0
// @ref _swprintf=00783764
// @ref ?unknown_command_text_a4153c@@3PAGA=00a4153c
// @ref ??_C@_0BA@NANB@D?3?2Ra2?2Init?4CPP?$AA@=007db8e4
// @ref ??_C@_0P@MKNI@TXT_TAUNT_DESC?$AA@=007dcb74

wchar_t const *TauntCommandClass::Get_Description() const
{
    swprintf(unknown_command_text_a4153c, StringTable::Load_String("TXT_TAUNT_DESC", 0, "D:\\Ra2\\Init.CPP", 6154), TauntNumber);
    return unknown_command_text_a4153c;
}
