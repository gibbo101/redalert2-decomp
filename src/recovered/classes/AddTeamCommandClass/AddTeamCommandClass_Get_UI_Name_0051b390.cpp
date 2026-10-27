// wchar_t const *AddTeamCommandClass::Get_UI_Name() const -- 0x0051B390
// The localized name (TXT_ADD_SELECT_TEAM) formatted with the team number
// into the shared command text buffer (0x00A4153C).
#include "shared/command.hpp"
// @ref ?Load_String@StringTable@@SIPBGPBDPAD0H@Z=006f9ec0
// @ref _swprintf=00783764
// @ref ?unknown_command_text_a4153c@@3PAGA=00a4153c
// @ref ??_C@_0BA@NANB@D?3?2Ra2?2Init?4CPP?$AA@=007db8e4
// @ref ??_C@_0BE@CHKG@TXT_ADD_SELECT_TEAM?$AA@=007dca98

wchar_t const *AddTeamCommandClass::Get_UI_Name() const
{
    swprintf(unknown_command_text_a4153c, StringTable::Load_String("TXT_ADD_SELECT_TEAM", 0, "D:\\Ra2\\Init.CPP", 6071), TeamNumber);
    return unknown_command_text_a4153c;
}
