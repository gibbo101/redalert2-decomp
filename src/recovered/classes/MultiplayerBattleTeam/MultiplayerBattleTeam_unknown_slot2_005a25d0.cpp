// bool MultiplayerBattleTeam::unknown_slot2(int unknown) -- 0x005A25D0
// Team slot 2: the MultiplayerTeam slot-2 test (0x005B9B80, called directly).
// @ref ?unknown_slot2@MultiplayerTeam@@UAE_NH@Z=005b9b80

bool MultiplayerBattleTeam::unknown_slot2(int unknown)
{
    return MultiplayerTeam::unknown_slot2(unknown) ? true : false;
}
