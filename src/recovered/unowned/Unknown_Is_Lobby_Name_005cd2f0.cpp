// bool __fastcall Unknown_Is_Lobby_Name_005cd2f0(Wstring const &name) (0x005CD2F0)
// True when name equals one of the seven fixed lobby entry names (Open, Closed,
// Waiting, EasyAI, MediumAI, HardAI, OpenObserver).
#include "shared/lobby.hpp"
// @ref ?unknown_lobby_names_7e6de8@@3PAPBDA=007e6de8
// @ref ??8Wstring@@QBE_NPBD@Z=0076da00

bool __fastcall Unknown_Is_Lobby_Name_005cd2f0(Wstring const &name)
{
    return name == unknown_lobby_names_7e6de8[0] || name == unknown_lobby_names_7e6de8[1] ||
           name == unknown_lobby_names_7e6de8[2] || name == unknown_lobby_names_7e6de8[3] ||
           name == unknown_lobby_names_7e6de8[4] || name == unknown_lobby_names_7e6de8[5] ||
           name == unknown_lobby_names_7e6de8[6];
}
