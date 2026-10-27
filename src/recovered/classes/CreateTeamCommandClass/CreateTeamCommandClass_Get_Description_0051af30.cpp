// wchar_t const *CreateTeamCommandClass::Get_Description() const -- 0x0051AF30
// The localized description (TXT_CREATE_TEAM_DESC) formatted with the team number
// into the shared command text buffer (0x00A4153C).
#include "shared/command.hpp"
// @ref ?Load_String@StringTable@@SIPBGPBDPAD0H@Z=006f9ec0
// @ref _swprintf=00783764
// @ref ?unknown_command_text_a4153c@@3PAGA=00a4153c
// @ref ??_C@_0BA@NANB@D?3?2Ra2?2Init?4CPP?$AA@=007db8e4
// @ref ??_C@_0BF@MKNN@TXT_CREATE_TEAM_DESC?$AA@=007dc900

wchar_t const *CreateTeamCommandClass::Get_Description() const
{
    swprintf(unknown_command_text_a4153c, StringTable::Load_String("TXT_CREATE_TEAM_DESC", 0, "D:\\Ra2\\Init.CPP", 5914), TeamNumber);
    return unknown_command_text_a4153c;
}
