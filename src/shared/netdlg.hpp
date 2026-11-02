// NetDlg.CPP's Init_Network and Shutdown_Network (0x005BB540, 0x005BB5A0): netdlg2.cpp's pair
// (lobby.hpp) without the lobby list calls. Conventions unevidenced: __cdecl and __fastcall compile alike.
// Not in lobby.hpp: new declarations there renumber the labels of the fragile row 0x0073FEE0.
#ifndef RA2_SHARED_NETDLG_HPP
#define RA2_SHARED_NETDLG_HPP

bool Init_Network_005bb540();
void Shutdown_Network_005bb5a0();

#ifndef _WCHAR_T_DEFINED
typedef unsigned short wchar_t;
#define _WCHAR_T_DEFINED
#endif

class ListClass;

// The CRC of a player name, upper-cased first (TibSun netdlg.cpp Compute_Name_CRC;
// 0x005BB9D0, and the wide-character copy 0x005BBA50).
unsigned long __fastcall Compute_Name_CRC(char const *name);
unsigned long __fastcall Compute_Name_CRC(wchar_t const *name);
// Deletes every text item of the list box, then flags it for redraw (TibSun
// Clear_Listbox; 0x005BBAD0).
void __fastcall Clear_Listbox(ListClass *list);

extern "C" char *__cdecl _strupr(char *string);                 // 0x007961E4
extern "C" wchar_t *__cdecl _wcsupr(wchar_t *string);           // 0x00796EF6
extern "C" wchar_t *__cdecl wcscpy(wchar_t *dest, wchar_t const *source);   // 0x00783689
extern "C" unsigned int __cdecl wcslen(wchar_t const *string);  // 0x00783605

#endif
