// MultiplayerTeam *__fastcall unknown_create_battle_team(int number) -- 0x005A2550
// Creates a MultiplayerBattleTeam for a team number, named by the number as
// wide text (0x007710C0); the constructor is expanded inline. Called by
// MultiplayerGameMode code (0x005B778D). Name is a hypothesis.
// @ref ?unknown_number_text_7710c0@@YI?AVWideString@@H@Z=007710c0
// @ref ??2@YAPAXI@Z=00782017
// @ref ??1WideString@@QAE@XZ=0076fa50

MultiplayerTeam *__fastcall unknown_create_battle_team_005a2550(int number)
{
    return new MultiplayerBattleTeam(unknown_number_text_7710c0(number), number);
}
