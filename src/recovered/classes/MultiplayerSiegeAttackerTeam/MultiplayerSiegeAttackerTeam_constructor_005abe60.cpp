// MultiplayerSiegeAttackerTeam::MultiplayerSiegeAttackerTeam() -- 0x005ABE60
// The siege attackers: team number 1 as well, named by the localized
// "MP:AttackerTeam" string.
// @ref ??_7MultiplayerSiegeAttackerTeam@@6B@=007a6c64
// @ref ??_GMultiplayerSiegeAttackerTeam@@UAEPAXI@Z=005abef0
// @ref ?unknown_slot1@MultiplayerTeam@@UAE_NH@Z=005b9b60
// @ref ??_C@_0BA@DGEJ@MP?3AttackerTeam?$AA@=007e57bc
// @ref ??0WideString@@QAE@PBG@Z=0076f9c0
// @ref ??1WideString@@QAE@XZ=0076fa50

MultiplayerSiegeAttackerTeam::MultiplayerSiegeAttackerTeam() :
    MultiplayerTeam(StringTable::Load_String("MP:AttackerTeam", 0, "D:\\Ra2\\MPSiegeTeam.cpp", 0x16), 1)
{
}
