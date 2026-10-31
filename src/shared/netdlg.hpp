// NetDlg.CPP's Init_Network and Shutdown_Network (0x005BB540, 0x005BB5A0): netdlg2.cpp's pair
// (lobby.hpp) without the lobby list calls. Conventions unevidenced: __cdecl and __fastcall compile alike.
// Not in lobby.hpp: new declarations there renumber the labels of the fragile row 0x0073FEE0.
#ifndef RA2_SHARED_NETDLG_HPP
#define RA2_SHARED_NETDLG_HPP

bool Init_Network_005bb540();
void Shutdown_Network_005bb5a0();

#endif
