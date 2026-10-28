// The skirmish and online game options dialog (0x005C3550): the session settings it shows.
#ifndef RA2_SHARED_OPTIONS_DIALOG_HPP
#define RA2_SHARED_OPTIONS_DIALOG_HPP
#include "shared/reference_counted.hpp"
class WDTTerritory;
extern int unknown_session_a3d2a0;              // 0x00A3D2A0 (session +0x08; a WDT territory index)
extern int unknown_a3d2a4;                     // 0x00A3D2A4 (1 or 2: an online session state; also in shared/wol_sink.hpp)
extern int unknown_session_a3d2bc;              // 0x00A3D2BC (session +0x24; the starting money)
extern int unknown_session_a3d2d0;              // 0x00A3D2D0 (session +0x38; the start units)
extern unsigned char unknown_session_a3d2c2;    // 0x00A3D2C2 (session +0x2A)
extern int unknown_session_a3d2c4;              // 0x00A3D2C4 (session +0x2C; the low byte is used)
extern int unknown_session_a3d340;              // 0x00A3D340 (session +0xA8; the low byte is used)
// The territory of a WDT slot (0x00769690; name hypothesis).
rc_ptr<WDTTerritory> __fastcall Unknown_Territory_00769690(int index);
// Fills the options dialog from the session (0x005C3550).
void __fastcall Unknown_Fill_Options_Dialog_005c3550(void *dialog, int initial);
#endif
