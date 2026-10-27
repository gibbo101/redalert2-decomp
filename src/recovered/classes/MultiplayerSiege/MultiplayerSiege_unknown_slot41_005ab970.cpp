// void MultiplayerSiege::unknown_slot41(DynamicVectorClass<MultiplayerTeam *> *teams) -- 0x005AB970
// Slot 41: the siege teams: observers, defenders, attackers.
// @ref ??0MultiplayerObserverTeam@@QAE@XZ=005aa7b0
// @ref ??0MultiplayerSiegeDefenderTeam@@QAE@XZ=005abdc0
// @ref ??0MultiplayerSiegeAttackerTeam@@QAE@XZ=005abe60
// @ref ??2@YAPAXI@Z=00782017

void MultiplayerSiege::unknown_slot41(DynamicVectorClass<MultiplayerTeam *> *teams)
{
    teams->Add(new MultiplayerObserverTeam);
    teams->Add(new MultiplayerSiegeDefenderTeam);
    teams->Add(new MultiplayerSiegeAttackerTeam);
}
