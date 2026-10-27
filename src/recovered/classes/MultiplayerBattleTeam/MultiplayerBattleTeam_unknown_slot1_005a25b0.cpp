// bool MultiplayerBattleTeam::unknown_slot1(int unknown) -- 0x005A25B0
// Team slot 1: the MultiplayerTeam slot-1 test (0x005B9B60, called directly).
// @ref ?unknown_slot1@MultiplayerTeam@@UAE_NH@Z=005b9b60

bool MultiplayerBattleTeam::unknown_slot1(int unknown)
{
    return MultiplayerTeam::unknown_slot1(unknown) ? true : false;
}
