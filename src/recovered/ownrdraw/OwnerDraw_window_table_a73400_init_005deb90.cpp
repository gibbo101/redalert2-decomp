// A second window-keyed table of the unit at 0x00A73400: the same wlib dictionary instantiation as the
// window procedure table 0x00A73688 (one out-of-line Shrink_Table, 0x00602730, serves both: 0x005EDCE1 calls
// it with 0x00A73400, 0x005F9913 with 0x00A73688): its dynamic initializer (0x005DEB90) and atexit destructor
// (0x005DEC30, the next draft).
// @ref ?unknown_window_table_a73400@@3V?$WolDictionary@PAUHWND__@@P6GJPAU1@IIJ@Z@@A=00a73400
// @ref ?unknown_hash_window_5de970@@YIIABQAUHWND__@@@Z=005de970
#include "shared/wol_dictionary.hpp"

unsigned int __fastcall unknown_hash_window_5de970(HWND const &key);

WolDictionary<HWND, WNDPROC> unknown_window_table_a73400(unknown_hash_window_5de970);
